#include "ResourceData.h"

FSoftObjectPath UResourceData::FindResourcePathForTag(const FGameplayTag& ResourceTag)
{
	const TSoftObjectPtr<UObject>* PathPtr = ResourcePaths.Find(ResourceTag);
	if (PathPtr == nullptr)
		return FSoftObjectPath();
	
	return (*PathPtr).ToSoftObjectPath();
}
