#include "VoxelCharacter.h"

#include "Chunk.h"
#include "CrackDecalBox.h"
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
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->SetupAttachment(GetRootComponent());
	
	GetCharacterMovement()->GravityScale = 1.f;
	GetCharacterMovement()->MaxWalkSpeed = 450.f;
	GetCharacterMovement()->JumpZVelocity = 600.f;

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

	VoxelGameMode = Cast<AVoxelGameMode>(UGameplayStatics::GetGameMode(this));
	CrackDecalBox = GetWorld()->SpawnActor<ACrackDecalBox>();
}

void AVoxelCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CheckTeleportPlayerToCenter();
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
		
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AVoxelCharacter::StartAttack);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &AVoxelCharacter::StopAttack);
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Triggered, this, &AVoxelCharacter::TryPlaceBlock);
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

void AVoxelCharacter::StartAttack()
{
	// TODO : 블럭 크랙 내기
	FIntVector HitChunkIndex, HitBlockIndex;
	if (LineTraceCrackBlock(HitChunkIndex, HitBlockIndex))
	{
		FVector WorldCenterPos = UVoxelFunctionLibrary::GetBlockCenterWorldPos(HitChunkIndex, HitBlockIndex);
		CrackDecalBox->SetVisibility(EBlockState::Crack1);
		CrackDecalBox->SetActorLocation(WorldCenterPos);
	}
	if (AttackTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(AttackTimerHandle);
		AttackTimerHandle.Invalidate();
	}
		
	// TODO: 타이머에서도 라인트레이스해서 블록을 해제 & 변경해야함
	GetWorldTimerManager().SetTimer(AttackTimerHandle, [this, HitChunkIndex, HitBlockIndex]()
	{
		EBlockState NewBlockState = static_cast<EBlockState>((static_cast<int32>(CrackDecalBox->GetBlockState()) + 1) % static_cast<int32>(EBlockState::Count));
		if (NewBlockState == EBlockState::NoCrack)
		{
			VoxelGameMode->UpdateBlockType(HitChunkIndex, HitBlockIndex, EBlockType::Air);
			StopAttack();
		}
		else
		{
			CrackDecalBox->SetVisibility(NewBlockState);
		}
	}, 0.25f, true);
}

void AVoxelCharacter::StopAttack()
{
	if (AttackTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(AttackTimerHandle);
		AttackTimerHandle.Invalidate();
	}
	
	CrackDecalBox->SetVisibility(EBlockState::NoCrack);
}

void AVoxelCharacter::TryPlaceBlock()
{
	FHitResult ChunkHitResult;
	if (LineTraceChunk(ChunkHitResult))
	{
		const FVector& BlockLocation = ChunkHitResult.ImpactPoint + (ChunkHitResult.ImpactNormal * (FVoxel::BlockSize / 2.f));
		const FIntVector& HitChunkIndex = UVoxelFunctionLibrary::WorldPosToChunkIndex(BlockLocation);
		const FIntVector& HitBlockIndex = UVoxelFunctionLibrary::WorldPosToBlockIndex(BlockLocation);
		const FVector& BlockCenterLocation = UVoxelFunctionLibrary::GetBlockCenterWorldPos(HitChunkIndex, HitBlockIndex);
		
		FHitResult PawnHitResult;
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
		
		if (UKismetSystemLibrary::BoxTraceSingleForObjects(this, BlockCenterLocation, BlockCenterLocation, FVector(FVoxel::BlockSize / 2.f),
			FRotator::ZeroRotator, ObjectTypes, false, TArray<AActor*>(), EDrawDebugTrace::None, PawnHitResult, false) == false)
		{
			VoxelGameMode->UpdateBlockType(HitChunkIndex, HitBlockIndex, EBlockType::Dirt);
		}
	}
}

void AVoxelCharacter::CheckTeleportPlayerToCenter()
{
	if (GetActorLocation().Z < 0)
	{
		const FIntVector& ChunkCount = FVoxel::ChunkCount;
		const FIntVector& BlockCount = FVoxel::BlockCount;
		int32 BlockSize = FVoxel::BlockSize;
		FIntVector ChunkSize = FIntVector(BlockCount.X * BlockSize, BlockCount.Y * BlockSize, BlockCount.Z * BlockSize);
		FVector MaxLocation = FVector(ChunkSize.X * ChunkCount.X, ChunkSize.Y * ChunkCount.Y, ChunkSize.Z * ChunkCount.Z);
		SetActorLocation(FVector(MaxLocation.X / 2.f, MaxLocation.Y / 2.f, MaxLocation.Z + 300.f));
	}
}

bool AVoxelCharacter::LineTraceChunk(FHitResult& OutHitResult)
{
	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + UKismetMathLibrary::GetForwardVector(CameraComponent->GetComponentRotation()) * LineTraceHitRange;
	TArray<AActor*> ActorsToIgnore = { this };
	FHitResult HitResult;
	if (UKismetSystemLibrary::LineTraceSingle(this, Start, End, TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true))
	{
		if (HitResult.GetActor() && HitResult.GetActor()->GetClass() == AChunk::StaticClass())
		{
			OutHitResult = HitResult;
			return true;
		}
	}
	return false;
}

bool AVoxelCharacter::LineTraceCrackBlock(FIntVector& OutHitChunkIndex, FIntVector& OutHitBlockIndex)
{
	FHitResult ChunkHitResult;
	if (LineTraceChunk(ChunkHitResult))
	{
		const FVector& BlockLocation = ChunkHitResult.ImpactPoint + (-ChunkHitResult.ImpactNormal * (FVoxel::BlockSize / 2.f));
		OutHitChunkIndex = UVoxelFunctionLibrary::WorldPosToChunkIndex(BlockLocation);
		OutHitBlockIndex = UVoxelFunctionLibrary::WorldPosToBlockIndex(BlockLocation);
		
		int ChunkIndex1D = UVoxelFunctionLibrary::Index3DTo1D(OutHitChunkIndex, FVoxel::ChunkCount);
		int BlockIndex1D = UVoxelFunctionLibrary::Index3DTo1D(OutHitBlockIndex, FVoxel::BlockCount);
		EBlockType BlockType = VoxelGameMode->ChunkDatas[ChunkIndex1D].BlockTypes[BlockIndex1D];
		if (BlockType == EBlockType::BedRock)
			return false;
		
		const FVector& BlockCenterLocation = UVoxelFunctionLibrary::GetBlockCenterWorldPos(OutHitChunkIndex, OutHitBlockIndex);
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
		TArray<AActor*> ActorsToIgnore = { CrackDecalBox };
		TArray<AActor*> OutActors;
		if (UKismetSystemLibrary::SphereOverlapActors(this, BlockCenterLocation, FVoxel::BlockSize / 2.f - 20.f,
			ObjectTypes, ACrackDecalBox::StaticClass(), ActorsToIgnore, OutActors))
			return false;

		return true;
	}
	return false;
}
