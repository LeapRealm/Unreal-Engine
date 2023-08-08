#include "Managers/ResourceManager.h"

#include "Utils/Define.h"

void UResourceManager::Init(UResourceData* InResourceData)
{
	ResourceData = InResourceData;
}

void UResourceManager::LoadAsync(const FGameplayTag& ResourceTag, TFunction<void(UObject*)> Callback, bool bAutoRelease)
{
	if (ResourceTag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild Resource Tag"));
		return;
	}
	
	if (ResourceData == nullptr)
	{
		LOG_ERROR(TEXT("Can't Find Resource Data"));
		return;
	}

	const FSoftObjectPath& ResourcePath = ResourceData->FindResourcePathForTag(ResourceTag);
	if (ResourcePath.IsValid() == false)
	{
		LOG_ERROR(TEXT("Can't Find Resource Path on Resource Data"));
		return;
	}

	if (UObject* Resource = ResourcePath.ResolveObject())
	{
		Callback(Resource);
		return;
	}
	
	const TSharedPtr<FStreamableHandle>* Handle = TagToHandle.Find(ResourceTag);
	if (Handle && (*Handle).IsValid() && (*Handle)->IsLoadingInProgress())
	{
		if (FResourceLoadCompletedDelegate* InternalDelegate = TagToDelegate.Find(ResourceTag))
			(*InternalDelegate).AddLambda(Callback);
		return;
	}
	
	FResourceLoadCompletedDelegate InternalDelegate;
	InternalDelegate.AddLambda(Callback);
	TagToDelegate.Add(ResourceTag, InternalDelegate);
	
	TagToHandle.Add(ResourceTag, StreamableManager.RequestAsyncLoad(ResourcePath, [ResourceTag, bAutoRelease, this]()
	{
		const TSharedPtr<FStreamableHandle>* Handle = TagToHandle.Find(ResourceTag);
		if (Handle && (*Handle).IsValid() && (*Handle)->HasLoadCompleted())
		{
			TagToDelegate.FindRef(ResourceTag).Broadcast((*Handle)->GetLoadedAsset());

			if (bAutoRelease)
				TagToHandle.Remove(ResourceTag);
		}
		TagToDelegate.Remove(ResourceTag);
	}));
}

void UResourceManager::Release(const FGameplayTag& ResourceTag)
{
	if (ResourceTag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild Resource Tag"));
		return;
	}

	const TSharedPtr<FStreamableHandle>* Handle = TagToHandle.Find(ResourceTag);
	if (Handle && (*Handle).IsValid())
	{
		(*Handle)->ReleaseHandle();
		TagToHandle.Remove(ResourceTag);
	}
}

void UResourceManager::Clear()
{
	for (const auto& Handle : TagToHandle)
	{
		if (Handle.Value.IsValid())
			Handle.Value->ReleaseHandle();
	}
	TagToHandle.Empty();
	TagToDelegate.Empty();
}

AActor* UResourceManager::SpawnActor(const FGameplayTag& ActorTag, const FVector& Location, const FRotator& Rotation, const FVector& Scale)
{
	if (ActorTag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild Actor Tag"));
		return nullptr;
	}
	
	if (ResourceData == nullptr)
	{
		LOG_ERROR(TEXT("Can't Find Resource Data"));
		return nullptr;
	}
	
	UClass* ActorClass = ResourceData->FindActorClassForTag(ActorTag);
	if (ActorClass == nullptr)
	{
		LOG_ERROR(TEXT("Can't Find Actor Class on Resource Data"));
		return nullptr;
	}

	FTransform Transform;
	Transform.SetLocation(Location);
	Transform.SetRotation(Rotation.Quaternion());
	Transform.SetScale3D(Scale);
	
	return GetWorld()->SpawnActor(ActorClass, &Transform, FActorSpawnParameters());
}

void UResourceManager::DestroyActor(AActor* Actor, float Seconds)
{
	if (Seconds > 0.f)
		Actor->SetLifeSpan(Seconds);
	else
		GetWorld()->DestroyActor(Actor);
}
