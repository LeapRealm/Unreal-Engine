#pragma once

#include "L1ExperienceDefinition.generated.h"

class UL1PawnData;

UCLASS(BlueprintType)
class UL1ExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UL1ExperienceDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(EditDefaultsOnly, Category=Gameplay)
	TObjectPtr<UL1PawnData> DefaultPawnData;

	UPROPERTY(EditDefaultsOnly, Category=Gameplay)
	TArray<FString> GameFeaturesToEnable;
};
