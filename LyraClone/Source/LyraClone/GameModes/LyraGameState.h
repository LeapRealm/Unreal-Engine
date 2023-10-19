#pragma once

#include "GameFramework/GameStateBase.h"
#include "LyraGameState.generated.h"

class ULyraExperienceManagerComponent;

UCLASS()
class ALyraGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ALyraGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY()
	TObjectPtr<ULyraExperienceManagerComponent> ExperienceManagerComponent;
};
