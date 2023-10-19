#include "LyraPlayerState.h"

#include "GameFramework/GameStateBase.h"
#include "LyraClone/GameModes/LyraExperienceDefinition.h"
#include "LyraClone/GameModes/LyraExperienceManagerComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraPlayerState)

ALyraPlayerState::ALyraPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void ALyraPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AGameStateBase* GameState = GetWorld()->GetGameState();
	check(GameState);

	ULyraExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<ULyraExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(FOnLyraExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void ALyraPlayerState::OnExperienceLoaded(const ULyraExperienceDefinition* CurrentExperience)
{
	
}
