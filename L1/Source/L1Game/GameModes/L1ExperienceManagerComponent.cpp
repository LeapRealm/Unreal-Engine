#include "L1ExperienceManagerComponent.h"

#include "GameFeaturesSubsystemSettings.h"
#include "L1ExperienceDefinition.h"
#include "System/L1AssetManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(L1ExperienceManagerComponent)

UL1ExperienceManagerComponent::UL1ExperienceManagerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UL1ExperienceManagerComponent::CallOrRegister_OnExperienceLoaded(FOnL1ExperienceLoaded::FDelegate&& Delegate)
{
	if (IsExperienceLoaded())
	{
		Delegate.Execute(CurrentExperience);
	}
	else
	{
		OnExperienceLoaded.Add(MoveTemp(Delegate));
	}
}

void UL1ExperienceManagerComponent::SetCurrentExperience(FPrimaryAssetId ExperienceID)
{
	UL1AssetManager& AssetManager = UL1AssetManager::Get();

	TSubclassOf<UL1ExperienceDefinition> AssetClass;
	{
		FSoftObjectPath AssetPath = AssetManager.GetPrimaryAssetPath(ExperienceID);
		AssetClass = Cast<UClass>(AssetPath.TryLoad());
	}

	const UL1ExperienceDefinition* Experience = GetDefault<UL1ExperienceDefinition>(AssetClass);
	check(Experience);
	check(CurrentExperience == nullptr);

	CurrentExperience = Experience;

	StartExperienceLoad();
}

void UL1ExperienceManagerComponent::StartExperienceLoad()
{
	check(CurrentExperience);
	check(LoadState == EL1ExperienceLoadState::Unloaded);

	LoadState = EL1ExperienceLoadState::Loading;

	UL1AssetManager& AssetManager = UL1AssetManager::Get();

	TSet<FPrimaryAssetId> BundleAssetList;
	BundleAssetList.Add(CurrentExperience->GetPrimaryAssetId());

	TArray<FName> BundlesToLoad;
	{
		const ENetMode OwnerNetMode = GetOwner()->GetNetMode();
		bool bLoadClient = GIsEditor || (OwnerNetMode != NM_DedicatedServer);
		bool bLoadServer = GIsEditor || (OwnerNetMode != NM_Client);
		if (bLoadClient)
		{
			BundlesToLoad.Add(UGameFeaturesSubsystemSettings::LoadStateClient);
		}
		if (bLoadServer)
		{
			BundlesToLoad.Add(UGameFeaturesSubsystemSettings::LoadStateServer);
		}
	}

	FStreamableDelegate OnAssetLoadedDelegate = FStreamableDelegate::CreateUObject(this, &ThisClass::OnExperienceLoadComplete);

	TSharedPtr<FStreamableHandle> Handle = AssetManager.ChangeBundleStateForPrimaryAssets(
		BundleAssetList.Array(), BundlesToLoad, {}, false, FStreamableDelegate(), FStreamableManager::AsyncLoadHighPriority);

	if (Handle.IsValid() == false || Handle->HasLoadCompleted())
	{
		FStreamableHandle::ExecuteDelegate(OnAssetLoadedDelegate);
	}
	else
	{
		Handle->BindCompleteDelegate(OnAssetLoadedDelegate);
		Handle->BindCancelDelegate(FStreamableDelegate::CreateLambda([OnAssetLoadedDelegate]()
		{
			if (OnAssetLoadedDelegate.IsBound())
			{
				OnAssetLoadedDelegate.Execute();
			}
		}));
	}
}

void UL1ExperienceManagerComponent::OnExperienceLoadComplete()
{
	OnExperienceFullLoadCompleted();
}

void UL1ExperienceManagerComponent::OnExperienceFullLoadCompleted()
{
	check(LoadState != EL1ExperienceLoadState::Loaded);

	LoadState = EL1ExperienceLoadState::Loaded;
	OnExperienceLoaded.Broadcast(CurrentExperience);
	OnExperienceLoaded.Clear();
}
