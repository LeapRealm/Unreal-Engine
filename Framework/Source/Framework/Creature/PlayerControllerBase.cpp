#include "Creature/PlayerControllerBase.h"

#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MonsterBase.h"
#include "PlayerBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Interface/TargetInterface.h"
#include "Manager/ResourceManager.h"
#include "System/SkillComponent.h"
#include "Util/Tag.h"
#include "Util/Util.h"

void APlayerControllerBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	DefaultMappingContext	= UUtil::GetResourceManager(this)->LoadSync<UInputMappingContext>(Tag::Asset_Input_DefaultMappingContext);
	MoveKeyboardAction		= UUtil::GetResourceManager(this)->LoadSync<UInputAction>(Tag::Asset_Input_MoveKeyboardAction);
	LeftMouseAction			= UUtil::GetResourceManager(this)->LoadSync<UInputAction>(Tag::Asset_Input_LeftMouseAction);
	HoldAction				= UUtil::GetResourceManager(this)->LoadSync<UInputAction>(Tag::Asset_Input_HoldAction);
}

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveKeyboardAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::MoveKeyboard);
		
		EnhancedInputComponent->BindAction(LeftMouseAction, ETriggerEvent::Started, this, &APlayerControllerBase::LeftMousePressed);
		EnhancedInputComponent->BindAction(LeftMouseAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::LeftMouseHeld);
		EnhancedInputComponent->BindAction(LeftMouseAction, ETriggerEvent::Completed, this, &APlayerControllerBase::LeftMouseReleased);
		
		EnhancedInputComponent->BindAction(HoldAction, ETriggerEvent::Started, this, &APlayerControllerBase::HoldPressed);
		EnhancedInputComponent->BindAction(HoldAction, ETriggerEvent::Completed, this, &APlayerControllerBase::HoldReleased);
	}
}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(DefaultMappingContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void APlayerControllerBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TickCursorTrace();
	AutoRunning();
}

void APlayerControllerBase::MoveKeyboard(const FInputActionValue& Value)
{
	const FVector2D InputVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APlayerBase* PlayerBase = Cast<APlayerBase>(GetCharacter()))
	{
		bAutoMoving = false;
		PlayerBase->AddMovementInput(ForwardDirection, InputVector.X);
		PlayerBase->AddMovementInput(RightDirection, InputVector.Y);
	}
}

void APlayerControllerBase::LeftMousePressed(const FInputActionValue& Value)
{
	PressTime = 0.f;
	bAutoMoving = false;
	bShouldAttacking = false;
}

void APlayerControllerBase::LeftMouseHeld(const FInputActionValue& Value)
{
	PressTime += GetWorld()->GetDeltaSeconds();

	if (TargetActor || bHoldKeyDown)
		return;
	
	if (APlayerBase* PlayerBase = Cast<APlayerBase>(GetCharacter()))
	{
		FHitResult HitResult;
		if (GetHitResultUnderCursor(ECC_GameTraceChannel1, false, HitResult))
		{
			Destination = HitResult.ImpactPoint + FVector(0.f, 0.f, PlayerBase->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
			const FVector WorldDirection = (Destination - PlayerBase->GetActorLocation()).GetSafeNormal();
			PlayerBase->AddMovementInput(WorldDirection);
		}
	}
}

void APlayerControllerBase::LeftMouseReleased(const FInputActionValue& Value)
{
	if (PressTime > PressThreshold)
		return;
	
	if (bHoldKeyDown)
	{
		if (APlayerBase* PlayerBase = Cast<APlayerBase>(GetCharacter()))
		{
			if (USkillComponent* SkillComponent = PlayerBase->GetSkillComponent())
				SkillComponent->Execute(Tag::Asset_Skill_Slash);
		}
	}
	else
	{
		if (AMonsterBase* MonsterBase = Cast<AMonsterBase>(TargetActor))
		{
			bAutoMoving = true;
			bShouldAttacking = true;
			Destination = MonsterBase->GetActorLocation();
			AutoRunAcceptanceRadius = 150.f;
		}
		else
		{
			bAutoMoving = true;
			AutoRunAcceptanceRadius = 50.f;
		}
	}
}

void APlayerControllerBase::TickCursorTrace()
{
	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECC_Visibility, false, OUT HitResult) == false)
		return;
	
	ITargetInterface* NewTargetActor = Cast<ITargetInterface>(HitResult.GetActor());
	if (NewTargetActor)
	{
		if (TargetActor)
		{
			if (TargetActor != NewTargetActor)
			{
				TargetActor->UnHighlightActor();
				NewTargetActor->HighlightActor();
			}
		}
		else
		{
			NewTargetActor->HighlightActor();
		}
	}
	else
	{
		if (TargetActor)
			TargetActor->UnHighlightActor();
	}

	TargetActor = NewTargetActor;
}

void APlayerControllerBase::AutoRunning()
{
	if (bAutoMoving == false)
		return;

	if (APlayerBase* PlayerBase = Cast<APlayerBase>(GetCharacter()))
	{
		const FVector WorldDirection = (Destination - PlayerBase->GetActorLocation()).GetSafeNormal();
		PlayerBase->AddMovementInput(WorldDirection);

		const float DistanceToDestination = (Destination - PlayerBase->GetActorLocation()).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoMoving = false;

			if (bShouldAttacking)
			{
				if (USkillComponent* SkillComponent = PlayerBase->GetSkillComponent())
					SkillComponent->Execute(Tag::Asset_Skill_Slash);
				
				bShouldAttacking = false;
			}
		}
	}
}
