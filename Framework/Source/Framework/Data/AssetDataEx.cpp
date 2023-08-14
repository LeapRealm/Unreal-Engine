#include "AssetDataEx.h"

#include "Widget/Widget_Base.h"

UClass* UAssetDataEx::FindObjectClassForTag(const FGameplayTag& ObjectTag) const
{
	const TSoftClassPtr<UObject>* ClassPtr = ObjectClasses.Find(ObjectTag);
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
