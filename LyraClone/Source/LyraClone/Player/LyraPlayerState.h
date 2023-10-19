#pragma once

#include "GameFramework/PlayerState.h"
#include "LyraPlayerState.generated.h"

class ULyraExperienceDefinition;
class ULyraPawnData;

UCLASS()
class ALyraPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ALyraPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void PostInitializeComponents() override;
	
public:
	void OnExperienceLoaded(const ULyraExperienceDefinition* CurrentExperience);
	
public:
	UPROPERTY()
	TObjectPtr<const ULyraPawnData> PawnData;
};
