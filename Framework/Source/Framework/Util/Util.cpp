#include "Util/Util.h"

#include "Kismet/GameplayStatics.h"
#include "Manager/Managers.h"

UManagers* UUtil::GetManagers(UObject* WorldContextObject)
{
	UManagers* Managers = Cast<UManagers>(UGameplayStatics::GetGameInstance(WorldContextObject));
	check(Managers);
	return Managers;
}

UDataManager* UUtil::GetDataManager(UObject* WorldContextObject)
{
	UDataManager* DataManager = GetManagers(WorldContextObject)->GetDataManager();
	check(DataManager);
	return DataManager;
}

UResourceManager* UUtil::GetResourceManager(UObject* WorldContextObject)
{
	UResourceManager* ResourceManager = GetManagers(WorldContextObject)->GetResourceManager();
	check(ResourceManager);
	return ResourceManager;
}

USceneManager* UUtil::GetSceneManager(UObject* WorldContextObject)
{
	USceneManager* SceneManager = GetManagers(WorldContextObject)->GetSceneManager();
	check(SceneManager);
	return SceneManager;
}

UWidgetManager* UUtil::GetWidgetManager(UObject* WorldContextObject)
{
	UWidgetManager* WidgetManager = GetManagers(WorldContextObject)->GetWidgetManager();
	check(WidgetManager);
	return WidgetManager;
}
