#pragma once

#include "LyraPawnData.generated.h"

class ULyraInputConfig;
class ULyraCameraMode;

UCLASS()
class ULyraPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	ULyraPawnData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Lyra|Pawn")
	TSubclassOf<APawn> PawnClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Lyra|Camera")
	TSubclassOf<ULyraCameraMode> DefaultCameraMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Lyra|InputConfig")
	TObjectPtr<ULyraInputConfig> InputConfig;
};
