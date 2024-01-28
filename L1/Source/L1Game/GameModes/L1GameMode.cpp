#include "L1GameMode.h"

#include "L1ExperienceManagerComponent.h"
#include "L1GameState.h"
#include "Character/L1Character.h"
#include "Player/L1PlayerController.h"
#include "Player/L1PlayerState.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(L1GameMode)

AL1GameMode::AL1GameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    GameStateClass = AL1GameState::StaticClass();
	PlayerControllerClass = AL1PlayerController::StaticClass();
	PlayerStateClass = AL1PlayerState::StaticClass();
	DefaultPawnClass = AL1Character::StaticClass();
}

void AL1GameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);
}

void AL1GameMode::InitGameState()
{
	Super::InitGameState();

	UL1ExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UL1ExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(FOnL1ExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void AL1GameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	if (IsExperienceLoaded())
	{
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	}
}

void AL1GameMode::HandleMatchAssignmentIfNotExpectingOne()
{
	FPrimaryAssetId ExperienceID;
	
	if (ExperienceID.IsValid() == false)
	{
		ExperienceID = FPrimaryAssetId(FPrimaryAssetType("L1ExperienceDefinition"), FName("B_L1DefaultExperience"));
	}

	OnMatchAssignmentGiven(ExperienceID);
}

void AL1GameMode::OnMatchAssignmentGiven(FPrimaryAssetId ExperienceID)
{
	check(ExperienceID.IsValid());

	UL1ExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UL1ExperienceManagerComponent>();
	check(ExperienceManagerComponent);
	ExperienceManagerComponent->SetCurrentExperience(ExperienceID);
}

void AL1GameMode::OnExperienceLoaded(const UL1ExperienceDefinition* CurrentExperience)
{
	
}

bool AL1GameMode::IsExperienceLoaded() const
{
	check(GameState);
	UL1ExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UL1ExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	return ExperienceManagerComponent->IsExperienceLoaded();
}
