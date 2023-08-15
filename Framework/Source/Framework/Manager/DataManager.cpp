#include "Manager/DataManager.h"

#include "Data/AssetDataEx.h"
#include "Data/GameData.h"

UDataManager::UDataManager()
{
	static ConstructorHelpers::FObjectFinder<UAssetDataEx> DA_AssetData(TEXT("/Script/Framework.AssetDataEx'/Game/Assets/Data/DA_AssetData.DA_AssetData'"));
	if (DA_AssetData.Succeeded())
		AssetData = DA_AssetData.Object;

	static ConstructorHelpers::FObjectFinder<UGameData> DA_GameData(TEXT("/Script/Framework.AssetDataEx'/Game/Assets/Data/DA_GameData.DA_GameData'"));
	if (DA_GameData.Succeeded())
		GameData = DA_GameData.Object;
}
