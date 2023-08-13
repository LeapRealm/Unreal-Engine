#include "AssetDataEx.h"

#include "Actor/ActorBase.h"
#include "Widget/Widget_Base.h"

UClass* UAssetDataEx::FindActorClassForTag(const FGameplayTag& ActorTag) const
{
	const TSoftClassPtr<AActorBase>* ClassPtr = ActorClasses.Find(ActorTag);
	if (ClassPtr == nullptr)
		return nullptr;
	
	return (*ClassPtr).LoadSynchronous();
}

FSoftObjectPath UAssetDataEx::FindResourcePathForTag(const FGameplayTag& ResourceTag) const
{
	const TSoftObjectPtr<UObject>* PathPtr = ResourcePaths.Find(ResourceTag);
	if (PathPtr == nullptr)
		return FSoftObjectPath();
	
	return (*PathPtr).ToSoftObjectPath();
}

UClass* UAssetDataEx::FindWidgetClassForTag(const FGameplayTag& WidgetTag) const
{
	const TSoftClassPtr<UWidget_Base>* ClassPtr = WidgetClasses.Find(WidgetTag);
	if (ClassPtr == nullptr)
		return nullptr;
	
	return (*ClassPtr).LoadSynchronous();
}
