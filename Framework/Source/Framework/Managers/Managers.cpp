#include "Managers/Managers.h"

#include "ActorManager.h"
#include "DataManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "UIManager.h"

UManagers::UManagers()
{
	ActorManager = CreateDefaultSubobject<UActorManager>(TEXT("ActorManager"));
	DataManager = CreateDefaultSubobject<UDataManager>(TEXT("DataManager"));
	ResourceManager = CreateDefaultSubobject<UResourceManager>(TEXT("ResourceManager"));
	SceneManager = CreateDefaultSubobject<USceneManager>(TEXT("SceneManager"));
	UIManager = CreateDefaultSubobject<UUIManager>(TEXT("UIManager"));
}

void UManagers::Init()
{
	Super::Init();
}

void UManagers::Tick(float DeltaTime)
{
	
}
