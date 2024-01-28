#include "L1AssetManager.h"

#include "L1LogChannels.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(L1AssetManager)

UL1AssetManager::UL1AssetManager()
	: Super()
{
	
}

UL1AssetManager& UL1AssetManager::Get()
{
	check(GEngine);

	if (UL1AssetManager* Singleton = Cast<UL1AssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LogL1, Fatal, TEXT("Invalid AssetManagerClassName in DefaultEngine.ini(project settings); it must be L1AssetManager"));
	return *NewObject<UL1AssetManager>();
}

bool UL1AssetManager::ShouldLogAssetLoads()
{
	static bool bLogAssetLoads = FParse::Param(FCommandLine::Get(), TEXT("LogAssetLoads"));
	return bLogAssetLoads;
}

UObject* UL1AssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	if (AssetPath.IsValid())
	{
		TUniquePtr<FScopeLogTime> LogTimePtr;
		if (ShouldLogAssetLoads())
		{
			LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("Synchronously loaded asset [%s]"), *AssetPath.ToString()), nullptr, FScopeLogTime::ScopeLog_Seconds);
		}

		if (UAssetManager::IsInitialized())
		{
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath);			
		}

		return AssetPath.TryLoad();
	}

	return nullptr;
}

void UL1AssetManager::AddLoadedAsset(const UObject* Asset)
{
	if (ensureAlways(Asset))
	{
		FScopeLock Lock(&SyncObject);
		LoadedAssets.Add(Asset);
	}
}

void UL1AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
}
