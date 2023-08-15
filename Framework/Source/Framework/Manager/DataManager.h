#pragma once

#include "CoreMinimal.h"
#include "Data/AssetDataEx.h"
#include "Data/GameData.h"
#include "DataManager.generated.h"

UCLASS()
class FRAMEWORK_API UDataManager : public UObject
{
	GENERATED_BODY()

public:
	UDataManager();

public:
	FORCEINLINE UClass* FindObjectClassForTag(const FGameplayTag& ObjectTag) const { return AssetData->FindObjectClassForTag(ObjectTag); }
	FORCEINLINE UClass* FindWidgetClassForTag(const FGameplayTag& WidgetTag) const { return AssetData->FindWidgetClassForTag(WidgetTag); }
	FORCEINLINE FSoftObjectPath FindResourcePathForTag(const FGameplayTag& ResourceTag) const { return AssetData->FindResourcePathForTag(ResourceTag); }
	FORCEINLINE const FInitialStatData& FindInitialStat(const FGameplayTag& CreatureTag) const { return GameData->FindInitialStat(CreatureTag); }
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAssetDataEx> AssetData;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UGameData> GameData;
};
