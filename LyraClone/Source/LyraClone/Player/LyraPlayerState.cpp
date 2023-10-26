#include "LyraPlayerState.h"

#include "GameFramework/GameStateBase.h"
#include "LyraClone/GameModes/LyraExperienceDefinition.h"
#include "LyraClone/GameModes/LyraExperienceManagerComponent.h"
#include "LyraClone/GameModes/LyraGameMode.h"

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

void ALyraPlayerState::SetPawnData(const ULyraPawnData* InPawnData)
{
	check(InPawnData);
	check(!PawnData);

	PawnData = InPawnData;
}

void ALyraPlayerState::OnExperienceLoaded(const ULyraExperienceDefinition* CurrentExperience)
{
	if (ALyraGameMode* GameMode = GetWorld()->GetAuthGameMode<ALyraGameMode>())
	{
		const ULyraPawnData* NewPawnData = GameMode->GetPawnDataForController(GetOwningController());
		check(NewPawnData);

		SetPawnData(NewPawnData);
	}
}
