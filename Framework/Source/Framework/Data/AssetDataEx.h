#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Widget/Widget_Base.h"
#include "Engine/DataAsset.h"
#include "AssetDataEx.generated.h"

UCLASS()
class FRAMEWORK_API UAssetDataEx : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE UClass* FindObjectClassForTag(const FGameplayTag& ObjectTag) const { return ObjectClasses.FindChecked(ObjectTag).LoadSynchronous(); }
	FORCEINLINE UClass* FindWidgetClassForTag(const FGameplayTag& WidgetTag) const { return WidgetClasses.FindChecked(WidgetTag).LoadSynchronous(); }
	FORCEINLINE FSoftObjectPath FindResourcePathForTag(const FGameplayTag& ResourceTag) const { return ResourcePaths.FindChecked(ResourceTag).ToSoftObjectPath(); }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, TSoftClassPtr<UObject>> ObjectClasses;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, TSoftClassPtr<UWidget_Base>> WidgetClasses;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, TSoftObjectPtr<UObject>> ResourcePaths;
};
