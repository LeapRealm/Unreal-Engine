#include "Util/Util.h"

#include "Kismet/GameplayStatics.h"
#include "Manager/Managers.h"

UManagers* UUtil::GetManagers(UObject* WorldContextObject)
{
	UManagers* Managers = Cast<UManagers>(UGameplayStatics::GetGameInstance(WorldContextObject));
	check(Managers);
	return Managers;
}

UActorManager* UUtil::GetActorManager(UObject* WorldContextObject)
{
	UActorManager* ActorManager = GetManagers(WorldContextObject)->GetActorManager();
	check(ActorManager);
	return ActorManager;
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

UWidgetManager* UUtil::GetUIManager(UObject* WorldContextObject)
{
	UWidgetManager* UIManager = GetManagers(WorldContextObject)->GetWidgetManager();
	check(UIManager);
	return UIManager;
}
