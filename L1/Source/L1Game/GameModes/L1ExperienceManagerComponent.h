#pragma once

#include "Components/GameStateComponent.h"
#include "L1ExperienceManagerComponent.generated.h"

class UL1ExperienceDefinition;

UENUM()
enum class EL1ExperienceLoadState
{
	Unloaded,
	Loading,
	Loaded,
	Deactivating
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnL1ExperienceLoaded, const UL1ExperienceDefinition*);

UCLASS()
class UL1ExperienceManagerComponent : public UGameStateComponent
{
	GENERATED_BODY()
	
public:
	UL1ExperienceManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void CallOrRegister_OnExperienceLoaded(FOnL1ExperienceLoaded::FDelegate&& Delegate);
	void SetCurrentExperience(FPrimaryAssetId ExperienceID);
	void StartExperienceLoad();
	void OnExperienceLoadComplete();
	void OnExperienceFullLoadCompleted();
	bool IsExperienceLoaded() { return (LoadState == EL1ExperienceLoadState::Loaded) && (CurrentExperience != nullptr); }
	
public:
	UPROPERTY()
	TObjectPtr<const UL1ExperienceDefinition> CurrentExperience;

	EL1ExperienceLoadState LoadState = EL1ExperienceLoadState::Unloaded;
	FOnL1ExperienceLoaded OnExperienceLoaded;
};
