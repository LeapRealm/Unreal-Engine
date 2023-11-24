#pragma once

#include "GameplayModMagnitudeCalculation.h"
#include "MaxHealthMagnitudeCalculation.generated.h"

UCLASS()
class UMaxHealthMagnitudeCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMaxHealthMagnitudeCalculation(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition VigorCapture;
	FGameplayEffectAttributeCaptureDefinition LevelCapture;
};
