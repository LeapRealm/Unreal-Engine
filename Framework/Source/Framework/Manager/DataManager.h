#pragma once

#include "CoreMinimal.h"
#include "Data/AssetDataEx.h"
#include "Data/GameData.h"
#include "DataManager.generated.h"

class UAssetDataEx;

UCLASS()
class FRAMEWORK_API UDataManager : public UObject
{
	GENERATED_BODY()

public:
	UDataManager();

public:
	UClass* FindObjectClassForTag(const FGameplayTag& ObjectTag) const { return AssetData->FindObjectClassForTag(ObjectTag); }
	FSoftObjectPath FindResourcePathForTag(const FGameplayTag& ResourceTag) const { return AssetData->FindResourcePathForTag(ResourceTag); }
	UClass* FindWidgetClassForTag(const FGameplayTag& WidgetTag) const { return AssetData->FindWidgetClassForTag(WidgetTag); }
	const TMap<FGameplayTag, FStatData>& GetInitialStats() const { return GameData->GetInitialStats(); }
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAssetDataEx> AssetData;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UGameData> GameData;
};
