#pragma once

#include "L1UserFacingExperienceDefinition.generated.h"

UCLASS()
class UL1UserFacingExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UL1UserFacingExperienceDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Experience, meta=(AllowedTypes="Map"))
	FPrimaryAssetId MapID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Experience, meta=(AllowedTypes="L1ExperienceDefinition"))
	FPrimaryAssetId ExperienceID;
};
