#pragma once

#include "GameFramework/GameModeBase.h"
#include "L1GameMode.generated.h"

class UL1ExperienceDefinition;

UCLASS()
class AL1GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AL1GameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

private:
	void HandleMatchAssignmentIfNotExpectingOne();
	void OnMatchAssignmentGiven(FPrimaryAssetId ExperienceID);
	void OnExperienceLoaded(const UL1ExperienceDefinition* CurrentExperience);
	bool IsExperienceLoaded() const;
};
