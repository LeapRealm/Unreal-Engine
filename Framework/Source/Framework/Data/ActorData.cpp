#include "Data/ActorData.h"

#include "Actor/ActorBase.h"

UClass* UActorData::FindActorClassForTag(const FGameplayTag& ActorTag)
{
	const TSoftClassPtr<AActorBase>* ClassPtr = ActorClasses.Find(ActorTag);
	if (ClassPtr == nullptr)
		return nullptr;
	
	return (*ClassPtr).LoadSynchronous();
}
