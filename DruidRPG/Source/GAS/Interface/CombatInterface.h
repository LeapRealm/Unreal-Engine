#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class GAS_API ICombatInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetPlayerLevel() { return 0; }
	virtual FVector GetCombatSocketLocation() { return FVector(); }

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateFacingTarget(const FVector& Target);
};
