#include "Creature/GASPlayer.h"

#include "AbilitySystemComponent.h"
#include "GASAbilitySystemComponent.h"
#include "GASPlayerController.h"
#include "GASPlayerState.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UI/HUD/GASHUD.h"

AGASPlayer::AGASPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 750.f;
	CameraBoom->SetRelativeRotation((FRotator(-45.f, 0.f, 0.f)));
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;
}

void AGASPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Server
	InitAbilityActorInfo();
}

void AGASPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Client
	InitAbilityActorInfo();
}

void AGASPlayer::InitAbilityActorInfo()
{
	Super::InitAbilityActorInfo();
	
	AGASPlayerState* GASPlayerState = GetPlayerState<AGASPlayerState>();
	check(GASPlayerState);
	GASPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(GASPlayerState, this);

	AbilitySystemComponent = GASPlayerState->GetAbilitySystemComponent();
	Cast<UGASAbilitySystemComponent>(AbilitySystemComponent)->OnSetAbilityActorInto();
	AttributeSet = GASPlayerState->GetAttributeSet();

	if (AGASPlayerController* GASPlayerController = Cast<AGASPlayerController>(GetController()))
	{
		if (AGASHUD* GASHUD = Cast<AGASHUD>(GASPlayerController->GetHUD()))
		{
			GASHUD->InitOverlay(GASPlayerController, GASPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	InitializePrimaryAttributes();
}
