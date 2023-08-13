#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AssetDataEx.generated.h"

class AActorBase;
class UWidget_Base;

UCLASS()
class FRAMEWORK_API UAssetDataEx : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UClass* FindActorClassForTag(const FGameplayTag& ActorTag) const;
	FSoftObjectPath FindResourcePathForTag(const FGameplayTag& ResourceTag) const;
	UClass* FindWidgetClassForTag(const FGameplayTag& WidgetTag) const;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, TSoftClassPtr<AActorBase>> ActorClasses;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, TSoftObjectPtr<UObject>> ResourcePaths;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, TSoftClassPtr<UWidget_Base>> WidgetClasses;
};
