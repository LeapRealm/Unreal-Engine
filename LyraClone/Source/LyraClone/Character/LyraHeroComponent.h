﻿#pragma once

#include "Components/GameFrameworkInitStateInterface.h"
#include "Components/PawnComponent.h"
#include "LyraHeroComponent.generated.h"

class ULyraCameraMode;

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class ULyraHeroComponent : public UPawnComponent, public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()
	
public:
	ULyraHeroComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual FName GetFeatureName() const override { return NAME_ActorFeatureName; }

	virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) override;
	virtual bool CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const override;
	virtual void CheckDefaultInitialization() override;
	virtual void HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) override;

public:
	TSubclassOf<ULyraCameraMode> DetermineCameraMode() const;
	
public:
	static const FName NAME_ActorFeatureName;
};
