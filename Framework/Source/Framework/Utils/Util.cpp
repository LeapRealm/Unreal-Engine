#include "Utils/Util.h"

#include "Kismet/GameplayStatics.h"
#include "Managers/Managers.h"

UResourceManager* UUtil::GetResourceManager(UObject* WorldContextObject)
{
	UManagers* Managers = Cast<UManagers>(UGameplayStatics::GetGameInstance(WorldContextObject));
	check(Managers);

	UResourceManager* ResourceManager = Managers->GetResourceManager();
	check(ResourceManager);
	
	return ResourceManager;
}

USceneManager* UUtil::GetSceneManager(UObject* WorldContextObject)
{
	UManagers* Managers = Cast<UManagers>(UGameplayStatics::GetGameInstance(WorldContextObject));
	check(Managers);

	USceneManager* SceneManager = Managers->GetSceneManager();
	check(SceneManager);
	
	return SceneManager;
}

UUIManager* UUtil::GetUIManager(UObject* WorldContextObject)
{
	UManagers* Managers = Cast<UManagers>(UGameplayStatics::GetGameInstance(WorldContextObject));
	check(Managers);

	UUIManager* UIManager = Managers->GetUIManager();
	check(UIManager);
	
	return UIManager;
}
