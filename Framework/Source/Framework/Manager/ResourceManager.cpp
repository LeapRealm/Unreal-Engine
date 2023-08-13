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
	
	const FSoftObjectPath& ResourcePath = UUtil::GetDataManager(this)->FindResourcePathForTag(ResourceTag);
	if (ResourcePath.IsValid() == false)
	{
		LOG_ERROR(TEXT("Can't Find Resource Path on Asset Data"));
		return;
	}

	StreamableManager.Unload(ResourcePath);
}
