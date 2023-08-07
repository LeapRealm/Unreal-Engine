#include "Managers/Managers.h"

#include "SceneManager.h"

UManagers::UManagers()
{
	SceneManager = CreateDefaultSubobject<USceneManager>(TEXT("SceneManager"));
}

void UManagers::Init()
{
	Super::Init();
}

void UManagers::Tick(float DeltaTime)
{
	
}
