#include "Manager/ResourceManager.h"

#include "DataManager.h"
#include "Util/Define.h"
#include "Util/Util.h"

void UResourceManager::Release(const FGameplayTag& ResourceTag)
{
	if (ResourceTag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild Resource Tag"));
		return;
	}

	UResourceData* ResourceData = UUtil::GetDataManager(this)->GetResourceData();
	const FSoftObjectPath& ResourcePath = ResourceData->FindResourcePathForTag(ResourceTag);
	if (ResourcePath.IsValid() == false)
	{
		LOG_ERROR(TEXT("Can't Find Resource Path on Resource Data"));
		return;
	}

	StreamableManager.Unload(ResourcePath);
}
