#pragma once

#include "LyraExperienceDefinition.generated.h"

class UGameFeatureAction;
class ULyraPawnData;
class ULyraExperienceActionSet;

UCLASS(BlueprintType)
class ULyraExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	ULyraExperienceDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(EditDefaultsOnly, Category=Gameplay)
	TObjectPtr<ULyraPawnData> DefaultPawnData;

	UPROPERTY(EditDefaultsOnly, Category=Gameplay)
	TArray<FString> GameFeaturesToEnable;

	// ExperienceActionSet은 UGameFeatureAction의 Set이며 분류의 목적으로 사용합니다.
	UPROPERTY(EditDefaultsOnly, Category=GamePlay)
	TArray<TObjectPtr<ULyraExperienceActionSet>> ActionSets;

	UPROPERTY(EditDefaultsOnly, Category=Actions)
	TArray<TObjectPtr<UGameFeatureAction>> Actions;
};
