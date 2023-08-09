#include "Data/ActorData.h"

#include "Actors/ActorBase.h"

UClass* UActorData::FindActorClassForTag(const FGameplayTag& ActorTag)
{
	const TSoftClassPtr<AActorBase>* ClassPtr = ActorClasses.Find(ActorTag);
	if (ClassPtr == nullptr)
		return nullptr;
	
	return (*ClassPtr).LoadSynchronous();
}
