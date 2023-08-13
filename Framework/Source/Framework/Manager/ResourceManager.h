#pragma once

#include "CoreMinimal.h"
#include "DataManager.h"
#include "Engine/StreamableManager.h"
#include "Util/Util.h"
#include "Util/Define.h"
#include "ResourceManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FResourceLoadCompletedDelegate, UObject*);

UCLASS()
class FRAMEWORK_API UResourceManager : public UObject
{
	GENERATED_BODY()

public:
	template<typename T>
	void LoadAsync(const FGameplayTag& ResourceTag, TFunction<void(T*)> Callback, bool bAutoRelease = true);
	void Release(const FGameplayTag& ResourceTag);

private:
	FStreamableManager StreamableManager;
};

template <typename T>
void UResourceManager::LoadAsync(const FGameplayTag& ResourceTag, TFunction<void(T*)> Callback, bool bAutoRelease)
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
	
	if (UObject* Resource = ResourcePath.ResolveObject())
	{
		Callback(Cast<T>(Resource));
		return;
	}
	
	StreamableManager.RequestAsyncLoad(ResourcePath, [ResourcePath, Callback]()
	{
		UObject* Object = ResourcePath.ResolveObject();
		if (Object == false)
		{
			LOG_ERROR(TEXT("Can't Load Resource"));
			return;
		}
		Callback(Cast<T>(Object));
	}, FStreamableManager::DefaultAsyncLoadPriority, !bAutoRelease);
}
