#pragma once

#include "CoreMinimal.h"
#include "Data/AssetDataEx.h"
#include "DataManager.generated.h"

class UAssetDataEx;

UCLASS()
class FRAMEWORK_API UDataManager : public UObject
{
	GENERATED_BODY()

public:
	UDataManager();

public:
	FORCEINLINE UClass* FindActorClassForTag(const FGameplayTag& ActorTag) const { return AssetData->FindActorClassForTag(ActorTag); }
	FORCEINLINE FSoftObjectPath FindResourcePathForTag(const FGameplayTag& ResourceTag) const { return AssetData->FindResourcePathForTag(ResourceTag); }
	FORCEINLINE UClass* FindWidgetClassForTag(const FGameplayTag& WidgetTag) const { return AssetData->FindWidgetClassForTag(WidgetTag); }
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAssetDataEx> AssetData;
};
