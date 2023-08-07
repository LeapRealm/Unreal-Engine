#include "Utils/Util.h"

#include "Kismet/GameplayStatics.h"
#include "Managers/Managers.h"

USceneManager* UUtil::GetSceneManager()
{
	UManagers* Managers = Cast<UManagers>(UGameplayStatics::GetGameInstance(GEngine->GetWorld()));
	check(Managers);

	USceneManager* SceneManager = Managers->GetSceneManager();
	check(SceneManager);
	
	return SceneManager;
}
