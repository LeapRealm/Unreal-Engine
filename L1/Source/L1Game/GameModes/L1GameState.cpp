#include "L1GameState.h"

#include "L1ExperienceManagerComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(L1GameState)

AL1GameState::AL1GameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    ExperienceManagerComponent = CreateDefaultSubobject<UL1ExperienceManagerComponent>("ExperienceManagerComponent");
}
