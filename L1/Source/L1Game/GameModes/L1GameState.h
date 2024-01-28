#pragma once

#include "GameFramework/GameStateBase.h"
#include "L1GameState.generated.h"

class UL1ExperienceManagerComponent;

UCLASS()
class AL1GameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AL1GameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY()
	TObjectPtr<UL1ExperienceManagerComponent> ExperienceManagerComponent;
};
