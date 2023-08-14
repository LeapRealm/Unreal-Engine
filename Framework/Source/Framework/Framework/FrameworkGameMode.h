#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FrameworkGameMode.generated.h"

UCLASS()
class FRAMEWORK_API AFrameworkGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFrameworkGameMode();
	
public:
	virtual void BeginPlay() override;
};
