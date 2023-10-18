#pragma once

#include "LyraUserFacingExperienceDefinition.generated.h"

UCLASS(BlueprintType)
class ULyraUserFacingExperienceDefinition : public UObject
{
	GENERATED_BODY()
	
public:
	ULyraUserFacingExperienceDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Experience, meta=(AllowedTypes="Map"))
	FPrimaryAssetId MapID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Experience, meta=(AllowedTypes="LyraExperienceDefinition"))
	FPrimaryAssetId ExperienceID;
};
