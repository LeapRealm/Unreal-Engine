#include "VoxelCharacter.h"

#include "Chunk.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "VoxelFunctionLibrary.h"
#include "VoxelGameMode.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

AVoxelCharacter::AVoxelCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Assets
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Default(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Default.IMC_Default'"));
	if (IMC_Default.Succeeded())
		DefaultMappingContext = IMC_Default.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Move(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Move.IA_Move'"));
	if (IA_Move.Succeeded())
		MoveAction = IA_Move.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Look(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Look.IA_Look'"));
	if (IA_Look.Succeeded())
		LookAction = IA_Look.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Jump(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Jump.IA_Jump'"));
	if (IA_Jump.Succeeded())
		JumpAction = IA_Jump.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Attack(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Attack.IA_Attack'"));
	if (IA_Attack.Succeeded())
		AttackAction = IA_Attack.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Interaction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Interaction.IA_Interaction'"));
	if (IA_Interaction.Succeeded())
		InteractionAction = IA_Interaction.Object;

	// Components
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetRootComponent());
	
	CameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	CameraComponent->bUsePawnControlRotation = true;
	
	GetCharacterMovement()->GravityScale = 1.f;
	GetCharacterMovement()->MaxWalkSpeed = 450.f;
	GetCharacterMovement()->JumpZVelocity = 700.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
}

void AVoxelCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AVoxelCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVoxelCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVoxelCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVoxelCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AVoxelCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AVoxelCharacter::StopJumping);
		
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AVoxelCharacter::Attack);
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Triggered, this, &AVoxelCharacter::Interaction);
	}
}

void AVoxelCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2D>();
	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MoveVector.X);
	AddMovementInput(RightDirection, MoveVector.Y);
}

void AVoxelCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void AVoxelCharacter::Attack()
{
	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + UKismetMathLibrary::GetForwardVector(CameraComponent->GetComponentRotation()) * LineTraceHitRange;
	TArray<AActor*> ActorsToIgnore = { this };
	FHitResult HitResult;
	if (UKismetSystemLibrary::LineTraceSingle(this, Start, End, TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true))
	{
		if (AChunk* HitChunk = Cast<AChunk>(HitResult.GetActor()))
		{
			const FVector& BlockLocation = HitResult.ImpactPoint + (-HitResult.ImpactNormal * (FVoxel::BlockSize / 2.f));
			const FIntVector& HitChunkIndex = HitChunk->ChunkIndex;
			const FIntVector& HitBlockIndex = UVoxelFunctionLibrary::WorldPosToBlockIndex(BlockLocation);

			if (AVoxelGameMode* VoxelGameMode = Cast<AVoxelGameMode>(UGameplayStatics::GetGameMode(this)))
				VoxelGameMode->UpdateBlockType(HitChunkIndex, HitBlockIndex, EBlockType::Air);
		}
	}
}

void AVoxelCharacter::Interaction()
{
	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + UKismetMathLibrary::GetForwardVector(CameraComponent->GetComponentRotation()) * LineTraceHitRange;
	TArray<AActor*> ActorsToIgnore = { this };
	FHitResult HitResult;
	if (UKismetSystemLibrary::LineTraceSingle(this, Start, End, TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true))
	{
		if (HitResult.GetActor() && HitResult.GetActor()->GetClass() == AChunk::StaticClass())
		{
			const FIntVector& BlockCount = FVoxel::BlockCount;
			int32 BlockSize = FVoxel::BlockSize;
			
			const FVector& BlockLocation = HitResult.ImpactPoint + (HitResult.ImpactNormal * (BlockSize / 2.f));
			const FIntVector& HitChunkIndex = UVoxelFunctionLibrary::WorldPosToChunkIndex(BlockLocation);
			const FIntVector& HitBlockIndex = UVoxelFunctionLibrary::WorldPosToBlockIndex(BlockLocation);
			
			FIntVector ChunkSize = FIntVector(BlockCount.X * BlockSize, BlockCount.Y * BlockSize, BlockCount.Z * BlockSize);
			FVector BlockCenterLocation = FVector(ChunkSize * HitChunkIndex) + FVector(HitBlockIndex * BlockSize) + FVector(BlockSize / 2.f);
			TArray<FHitResult> HitResults;
			TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
			ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
			
			if (UKismetSystemLibrary::BoxTraceMultiForObjects(this, BlockCenterLocation, BlockCenterLocation, FVector(BlockSize / 2.f), FRotator::ZeroRotator,
				ObjectTypes, false, TArray<AActor*>(), EDrawDebugTrace::ForDuration, HitResults, false) == false)
			{
				if (AVoxelGameMode* VoxelGameMode = Cast<AVoxelGameMode>(UGameplayStatics::GetGameMode(this)))
					VoxelGameMode->UpdateBlockType(HitChunkIndex, HitBlockIndex, EBlockType::Dirt);
			}
		}
	}
}
