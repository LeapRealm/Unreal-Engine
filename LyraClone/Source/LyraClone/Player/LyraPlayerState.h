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
	template<class T>
	const T* GetPawnData() const  { return Cast<T>(PawnData); }
	void SetPawnData(const ULyraPawnData* InPawnData);

	void OnExperienceLoaded(const ULyraExperienceDefinition* CurrentExperience);
	
public:
	UPROPERTY()
	TObjectPtr<const ULyraPawnData> PawnData;
};
