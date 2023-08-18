#include "Creature/PlayerControllerBase.h"

#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MonsterBase.h"
#include "PlayerBase.h"
#include "Components/CapsuleComponent.h"
#include "Interface/TargetInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Manager/ResourceManager.h"
#include "Manager/WidgetManager.h"
#include "System/SkillComponent.h"
#include "System/StatComponent.h"
#include "Util/Tag.h"
#include "Util/Util.h"
#include "Widget/Scene/Widget_Scene.h"

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

	UWidget_Scene* SceneWidget = UUtil::GetWidgetManager(this)->ShowSceneWidget<UWidget_Scene>(Tag::Asset_Widget_Scene);
	if (APlayerBase* PlayerBase = Cast<APlayerBase>(GetCharacter()))
	{
		PlayerBase->GetStatComponent()->AddDelegate(Tag::Stat_Health, SceneWidget, &UWidget_Scene::RefreshUI);
		PlayerBase->GetStatComponent()->AddDelegate(Tag::Stat_Mana, SceneWidget, &UWidget_Scene::RefreshUI);
	}
}

void APlayerControllerBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	HighlightTrace();
	AutoMoving();
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
	TargetActor = nullptr;

	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
	{
		if (Cast<ITargetInterface>(HitResult.GetActor()))
			TargetActor = HitResult.GetActor();
	}
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
			TargetLocation = HitResult.ImpactPoint + FVector(0.f, 0.f, PlayerBase->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
			const FVector WorldDirection = (TargetLocation - PlayerBase->GetActorLocation()).GetSafeNormal();
			PlayerBase->AddMovementInput(WorldDirection);
		}
	}
}

void APlayerControllerBase::LeftMouseReleased(const FInputActionValue& Value)
{
	if (PressTime > PressThreshold)
		return;
	
	APlayerBase* PlayerBase = Cast<APlayerBase>(GetCharacter());
	if (PlayerBase == nullptr)
		return;
	
	if (bHoldKeyDown)
	{
		FHitResult HitResult;
		if (GetHitResultUnderCursor(ECC_GameTraceChannel1, false, HitResult))
		{
			if (USkillComponent* SkillComponent = PlayerBase->GetSkillComponent())
			{
				if (SkillComponent->CanExecute(Tag::Skill_Slash))
				{
					FRotator Rotation = PlayerBase->GetActorRotation();
					Rotation.Yaw = UKismetMathLibrary::FindLookAtRotation(PlayerBase->GetActorLocation(), HitResult.ImpactPoint).Yaw;
					PlayerBase->SetActorRotation(Rotation);
					SkillComponent->Execute(Tag::Skill_Slash);
				}
			}
		}
	}
	else
	{
		if (Cast<AMonsterBase>(TargetActor))
		{
			bAutoMoving = true;
			AutoRunAcceptanceRadius = 150.f;
		}
		else
		{
			bAutoMoving = true;
			AutoRunAcceptanceRadius = 50.f;
		}
	}
}

void APlayerControllerBase::HighlightTrace()
{
	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECC_Visibility, false, OUT HitResult) == false)
		return;
	
	ITargetInterface* NewHighlightActor = Cast<ITargetInterface>(HitResult.GetActor());
	if (NewHighlightActor)
	{
		if (HighlightActor)
		{
			if (HighlightActor != NewHighlightActor)
			{
				HighlightActor->UnHighlightActor();
				NewHighlightActor->HighlightActor();
			}
		}
		else
		{
			NewHighlightActor->HighlightActor();
		}
	}
	else
	{
		if (HighlightActor)
			HighlightActor->UnHighlightActor();
	}

	HighlightActor = NewHighlightActor;
}

void APlayerControllerBase::AutoMoving()
{
	if (bAutoMoving == false)
		return;
	
	if (APlayerBase* PlayerBase = Cast<APlayerBase>(GetCharacter()))
	{
		if (AMonsterBase* MonsterBase = Cast<AMonsterBase>(TargetActor))
			TargetLocation = MonsterBase->GetActorLocation();
		
		const FVector WorldDirection = (TargetLocation - PlayerBase->GetActorLocation()).GetSafeNormal();
		PlayerBase->AddMovementInput(WorldDirection);
		
		const float DistanceToDestination = (TargetLocation - PlayerBase->GetActorLocation()).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoMoving = false;
			if (AMonsterBase* MonsterBase = Cast<AMonsterBase>(TargetActor))
			{
				if (USkillComponent* SkillComponent = PlayerBase->GetSkillComponent())
				{
					if (SkillComponent->CanExecute(Tag::Skill_Slash))
					{
						FRotator Rotation = PlayerBase->GetActorRotation();
						Rotation.Yaw = UKismetMathLibrary::FindLookAtRotation(PlayerBase->GetActorLocation(), MonsterBase->GetActorLocation()).Yaw;
						PlayerBase->SetActorRotation(Rotation);
						SkillComponent->Execute(Tag::Skill_Slash);
						TargetActor = nullptr;
					}
					else
					{
						bAutoMoving = true;
					}
				}
			}
		}
	}
}
