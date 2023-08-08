#include "Managers/Managers.h"

#include "SceneManager.h"
#include "ResourceManager.h"
#include "UIManager.h"

UManagers::UManagers()
{
	ResourceManager = CreateDefaultSubobject<UResourceManager>(TEXT("ResourceManager"));
	SceneManager = CreateDefaultSubobject<USceneManager>(TEXT("SceneManager"));
	UIManager = CreateDefaultSubobject<UUIManager>(TEXT("UIManager"));
}

void UManagers::Init()
{
	Super::Init();

	ResourceManager->Init(ResourceData);
}

void UManagers::Tick(float DeltaTime)
{
	
}
