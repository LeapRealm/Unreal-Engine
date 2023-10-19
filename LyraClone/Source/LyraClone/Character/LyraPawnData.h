﻿#pragma once

#include "LyraPawnData.generated.h"

UCLASS()
class ULyraPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	ULyraPawnData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Lyra|Pawn")
	TSubclassOf<APawn> PawnClass;
};
