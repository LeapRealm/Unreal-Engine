#pragma once

#include "LyraPawnData.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "Components/PawnComponent.h"
#include "LyraPawnExtensionComponent.generated.h"

class ULyraPawnData;

UCLASS()
class ULyraPawnExtensionComponent : public UPawnComponent, public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()
	
public:
	ULyraPawnExtensionComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	static ULyraPawnExtensionComponent* FindPawnExtensionComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<ULyraPawnExtensionComponent>() : nullptr); }
	
public:
	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual FName GetFeatureName() const override { return NAME_ActorFeatureName; }

	virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) override;
	virtual bool CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const override;
	virtual void CheckDefaultInitialization() override;

public:
	void SetPawnData(const ULyraPawnData* InPawnData);
	void SetupPlayerInputComponent();
	
public:
	static const FName NAME_ActorFeatureName;

	UPROPERTY(EditInstanceOnly, Category="Lyra|Pawn")
	TObjectPtr<const ULyraPawnData> PawnData;
};
