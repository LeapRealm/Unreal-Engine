#pragma once

#include "Components/GameStateComponent.h"

#include "LyraExperienceManagerComponent.generated.h"

namespace UE::GameFeatures { struct FResult; }
class ULyraExperienceDefinition;

enum class ELyraExperienceLoadState
{
	Unloaded,
	Loading,
	LoadingGameFeatures,
	ExecutingActions,
	Loaded,
	Deactivating,
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLyraExperienceLoaded, const ULyraExperienceDefinition*);

UCLASS()
class ULyraExperienceManagerComponent : public UGameStateComponent
{
	GENERATED_BODY()
	
public:
	ULyraExperienceManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	bool IsExperienceLoaded() { return (LoadState == ELyraExperienceLoadState::Loaded) && (CurrentExperience != nullptr); }
	void CallOrRegister_OnExperienceLoaded(FOnLyraExperienceLoaded::FDelegate&& Delegate);

	void ServerSetCurrentExperience(FPrimaryAssetId ExperienceId);
	void StartExperienceLoad();
	void OnExperienceLoadComplete();
	void OnGameFeaturePluginLoadComplete(const UE::GameFeatures::FResult& Result);
	void OnExperienceFullLoadCompleted();
	
	const ULyraExperienceDefinition* GetCurrentExperienceChecked() const;

private:
	UPROPERTY()
	TObjectPtr<const ULyraExperienceDefinition> CurrentExperience;

	FOnLyraExperienceLoaded OnExperienceLoaded;
	ELyraExperienceLoadState LoadState = ELyraExperienceLoadState::Unloaded;

	// 활성화시킬 GameFeature Plugin들을 위한 변수
	int32 NumGameFeaturePluginsLoading = 0;
	TArray<FString> GameFeaturePluginURLs;
};
