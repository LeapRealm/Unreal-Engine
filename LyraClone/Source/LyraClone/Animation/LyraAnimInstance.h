#pragma once

#include "LyraAnimInstance.generated.h"

UCLASS()
class ULyraAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	ULyraAnimInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(BlueprintReadOnly, Category="Character State Data")
	float GroundDistance = -1.f;
};
