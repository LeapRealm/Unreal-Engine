#include "Manager/Managers.h"

#include "DataManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "WidgetManager.h"

UManagers::UManagers()
{
	DataManager = CreateDefaultSubobject<UDataManager>(TEXT("DataManager"));
	ResourceManager = CreateDefaultSubobject<UResourceManager>(TEXT("ResourceManager"));
	SceneManager = CreateDefaultSubobject<USceneManager>(TEXT("SceneManager"));
	WidgetManager = CreateDefaultSubobject<UWidgetManager>(TEXT("WidgetManager"));
}

void UManagers::Init()
{
	Super::Init();
}

void UManagers::Tick(float DeltaTime)
{
	
}
