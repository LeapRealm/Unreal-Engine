#pragma once

#include "LyraExperienceActionSet.generated.h"

class UGameFeatureAction;

UCLASS(BlueprintType)
class ULyraExperienceActionSet : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	ULyraExperienceActionSet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(EditAnywhere, Category="Actions to Perform")
	TArray<TObjectPtr<UGameFeatureAction>> Actions;
};
