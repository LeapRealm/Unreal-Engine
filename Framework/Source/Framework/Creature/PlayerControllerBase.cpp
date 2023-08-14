#include "Creature/PlayerControllerBase.h"

#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Interface/TargetInterface.h"
#include "Manager/ResourceManager.h"
#include "Util/Tag.h"
#include "Util/Util.h"

void APlayerControllerBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	DefaultMappingContext	= UUtil::GetResourceManager(this)->LoadSync<UInputMappingContext>(Tag::Asset_Input_DefaultMappingContext);
	MoveKeyboardAction		= UUtil::GetResourceManager(this)->LoadSync<UInputAction>(Tag::Asset_Input_MoveKeyboardAction);
	MoveMouseAction			= UUtil::GetResourceManager(this)->LoadSync<UInputAction>(Tag::Asset_Input_MoveMouseAction);
	HoldAction				= UUtil::GetResourceManager(this)->LoadSync<UInputAction>(Tag::Asset_Input_HoldAction);
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

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveKeyboardAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::MoveKeyboard);
		
		EnhancedInputComponent->BindAction(MoveMouseAction, ETriggerEvent::Started, this, &APlayerControllerBase::MoveMousePressed);
		EnhancedInputComponent->BindAction(MoveMouseAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::MoveMouseHeld);
		EnhancedInputComponent->BindAction(MoveMouseAction, ETriggerEvent::Completed, this, &APlayerControllerBase::MoveMouseReleased);
		
		EnhancedInputComponent->BindAction(HoldAction, ETriggerEvent::Started, this, &APlayerControllerBase::HoldPressed);
		EnhancedInputComponent->BindAction(HoldAction, ETriggerEvent::Completed, this, &APlayerControllerBase::HoldReleased);
	}
}

void APlayerControllerBase::MoveKeyboard(const FInputActionValue& Value)
{
	const FVector2D InputVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputVector.X);
		ControlledPawn->AddMovementInput(RightDirection, InputVector.Y);
	}
}

void APlayerControllerBase::MoveMousePressed(const FInputActionValue& Value)
{
	bAutoRunning = false;
}

void APlayerControllerBase::MoveMouseHeld(const FInputActionValue& Value)
{
	if (bHoldKeyDown)
		return;
	
	PressTime += GetWorld()->GetDeltaSeconds();

	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
		Destination = HitResult.ImpactPoint;

	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector WorldDirection = (Destination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection);
	}
}

void APlayerControllerBase::MoveMouseReleased(const FInputActionValue& Value)
{
	if (bHoldKeyDown)
		return;
	
	APawn* ControlledPawn = GetPawn();
	if (PressTime <= ShortPressThreshold && ControlledPawn)
		bAutoRunning = true;
	PressTime = 0.f;
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
	
}
