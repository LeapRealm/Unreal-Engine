#pragma once

#include "GameFramework/GameModeBase.h"
#include "LyraGameMode.generated.h"

class ULyraExperienceDefinition;

UCLASS()
class ALyraGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ALyraGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

public:
	void HandleMatchAssignmentIfNotExpectingOne();
	void OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId);
	
	bool IsExperienceLoaded() const;
	void OnExperienceLoaded(const ULyraExperienceDefinition* CurrentExperience);
};
