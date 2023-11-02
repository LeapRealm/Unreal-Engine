#pragma once

#include "GameplayModMagnitudeCalculation.h"
#include "MaxHealthCalculation.generated.h"

UCLASS()
class UMaxHealthCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMaxHealthCalculation(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition VigorCapture;
	FGameplayEffectAttributeCaptureDefinition LevelCapture;
};
