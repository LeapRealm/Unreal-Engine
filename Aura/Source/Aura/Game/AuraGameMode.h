#pragma once

#include "GameFramework/GameModeBase.h"
#include "AuraGameMode.generated.h"

UCLASS()
class AAuraGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AAuraGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
