#pragma once

#include "GameFramework/PlayerState.h"
#include "L1PlayerState.generated.h"

class UL1PawnData;
class UL1ExperienceDefinition;

UCLASS()
class AL1PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AL1PlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void PostInitializeComponents() override;

private:
	void OnExperienceLoaded(const UL1ExperienceDefinition* CurrentExperience);
	void SetPawnData(const UL1PawnData* InPawnData);

public:
	UPROPERTY()
	TObjectPtr<const UL1PawnData> PawnData;
};
