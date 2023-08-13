#include "Manager/DataManager.h"

#include "..\Data\AssetDataEx.h"

UDataManager::UDataManager()
{
	static ConstructorHelpers::FObjectFinder<UAssetDataEx> DA_AssetData(TEXT("/Script/Framework.ActorData'/Game/Data/DA_AssetData.DA_AssetData'"));
	if (DA_AssetData.Succeeded())
		AssetData = DA_AssetData.Object;
}
