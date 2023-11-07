#pragma once

#include "GameFramework/GameModeBase.h"
#include "LyraClone/Character/LyraPawnData.h"
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
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	
public:
	void HandleMatchAssignmentIfNotExpectingOne();
	void OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId);
	
	bool IsExperienceLoaded() const;
	void OnExperienceLoaded(const ULyraExperienceDefinition* CurrentExperience);

	const ULyraPawnData* GetPawnDataForController(const AController* InController) const;
};
