#pragma once

#include "GameplayTagContainer.h"
#include "AuraAbilityInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraAbilityInfoEntry
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag = FGameplayTag();

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag InputTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag CooldownTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UTexture2D> Icon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UMaterialInstance> BackgroundMaterial = nullptr;
};

UCLASS()
class UAuraAbilityInfoSet : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UAuraAbilityInfoSet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	FAuraAbilityInfoEntry FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound = false) const;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraAbilityInfoEntry> AbilityInfos;
};
