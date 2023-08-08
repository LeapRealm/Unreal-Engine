#include "ResourceData.h"

#include "Blueprint/UserWidget.h"

FSoftObjectPath UResourceData::FindResourcePathForTag(const FGameplayTag& ResourceTag)
{
	const TSoftObjectPtr<UObject>* PathPtr = ResourcePaths.Find(ResourceTag);
	if (PathPtr == nullptr)
		return FSoftObjectPath();
	
	return (*PathPtr).ToSoftObjectPath();
}

UClass* UResourceData::FindActorClassForTag(const FGameplayTag& ActorTag)
{
	const TSoftClassPtr<AActor>* ClassPtr = ActorClasses.Find(ActorTag);
	if (ClassPtr == nullptr)
		return nullptr;
	
	return (*ClassPtr).LoadSynchronous();
}

UClass* UResourceData::FindWidgetClassForTag(const FGameplayTag& WidgetTag)
{
	const TSoftClassPtr<UUserWidget>* ClassPtr = WidgetClasses.Find(WidgetTag);
	if (ClassPtr == nullptr)
		return nullptr;
	
	return (*ClassPtr).LoadSynchronous();
}
