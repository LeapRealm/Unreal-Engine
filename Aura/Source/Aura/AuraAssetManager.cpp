#include "AuraAssetManager.h"

#include "AuraGameplayTags.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraAssetManager)

UAuraAssetManager::UAuraAssetManager()
	: Super()
{
    
}

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);

	if (UAuraAssetManager* Singleton = Cast<UAuraAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LogTemp, Fatal, TEXT("Invalid AssetManagerClassName in DefaultEngine.ini(project settings); it must be LyraAssetManager"));
	return *NewObject<UAuraAssetManager>();
}

bool UAuraAssetManager::ShouldLogAssetLoads()
{
	static bool bLogAssetLoads = FParse::Param(FCommandLine::Get(), TEXT("LogAssetLoads"));
	return bLogAssetLoads;
}

UObject* UAuraAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
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

void UAuraAssetManager::AddLoadedAsset(const UObject* Asset)
{
	if (ensureAlways(Asset))
	{
		FScopeLock Lock(&SyncObject);
		LoadedAssets.Add(Asset);
	}
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAuraGameplayTags::InitializeNativeTags();
}
