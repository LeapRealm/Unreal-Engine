#include "Managers/DataManager.h"

#include "Data/ActorData.h"
#include "Data/ResourceData.h"
#include "..\Data\UIData.h"

UDataManager::UDataManager()
{
	static ConstructorHelpers::FObjectFinder<UActorData> DA_ActorData(TEXT("/Script/Framework.ActorData'/Game/Data/DA_ActorData.DA_ActorData'"));
	if (DA_ActorData.Succeeded())
		ActorData = DA_ActorData.Object;

	static ConstructorHelpers::FObjectFinder<UResourceData> DA_ResourceData(TEXT("/Script/Framework.ActorData'/Game/Data/DA_ResourceData.DA_ResourceData'"));
	if (DA_ResourceData.Succeeded())
		ResourceData = DA_ResourceData.Object;

	static ConstructorHelpers::FObjectFinder<UUIData> DA_UIData(TEXT("/Script/Framework.ActorData'/Game/Data/DA_UIData.DA_UIData'"));
	if (DA_UIData.Succeeded())
		UIData = DA_UIData.Object;
}
