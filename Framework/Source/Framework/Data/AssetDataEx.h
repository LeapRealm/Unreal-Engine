#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AssetDataEx.generated.h"

class UWidget_Base;

UCLASS()
class FRAMEWORK_API UAssetDataEx : public UDataAsset
{
	GENERATED_BODY()

public:
	UClass* FindObjectClassForTag(const FGameplayTag& ObjectTag) const;
	FSoftObjectPath FindResourcePathForTag(const FGameplayTag& ResourceTag) const;
	UClass* FindWidgetClassForTag(const FGameplayTag& WidgetTag) const;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, TSoftClassPtr<UObject>> ObjectClasses;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, TSoftObjectPtr<UObject>> ResourcePaths;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, TSoftClassPtr<UWidget_Base>> WidgetClasses;
};
