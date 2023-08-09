#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ResourceData.generated.h"

UCLASS()
class FRAMEWORK_API UResourceData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	FSoftObjectPath FindResourcePathForTag(const FGameplayTag& ResourceTag);
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, TSoftObjectPtr<UObject>> ResourcePaths;
};