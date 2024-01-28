#include "L1PlayerState.h"

#include "GameModes/L1ExperienceManagerComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(L1PlayerState)

AL1PlayerState::AL1PlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void AL1PlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AGameStateBase* GameState = GetWorld()->GetGameState();
	check(GameState);

	UL1ExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UL1ExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(FOnL1ExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void AL1PlayerState::OnExperienceLoaded(const UL1ExperienceDefinition* CurrentExperience)
{
	
}

void AL1PlayerState::SetPawnData(const UL1PawnData* InPawnData)
{
	check(InPawnData);
	check(PawnData == nullptr);
	
	PawnData = InPawnData;
}
