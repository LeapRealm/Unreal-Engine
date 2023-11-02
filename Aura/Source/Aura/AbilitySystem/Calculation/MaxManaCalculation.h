#pragma once

#include "GameplayModMagnitudeCalculation.h"
#include "MaxManaCalculation.generated.h"

UCLASS()
class UMaxManaCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMaxManaCalculation(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition IntelligenceCapture;
	FGameplayEffectAttributeCaptureDefinition LevelCapture;
};
