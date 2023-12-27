#pragma once

#include "AuraGameplayAbility.h"
#include "AuraSummonAbility.generated.h"

UCLASS()
class UAuraSummonAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
public:
	UAuraSummonAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();

	UFUNCTION(BlueprintPure)
	TSubclassOf<APawn> GetRandomMinionClass();
	
public:

	UPROPERTY(EditDefaultsOnly)
	int32 NumMinions = 5;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditDefaultsOnly)
	float MinSpawnDistance = 50.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxSpawnDistance = 250.f;

	UPROPERTY(EditDefaultsOnly)
	float SpawnSpread = 90.f;
};
