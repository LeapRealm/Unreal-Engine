#pragma once

#include "L1PawnData.generated.h"

UCLASS(BlueprintType)
class UL1PawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UL1PawnData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="L1|Pawn")
	TSubclassOf<APawn> PawnClass;
};
