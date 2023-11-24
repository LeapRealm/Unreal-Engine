#pragma once

#include "GameplayModMagnitudeCalculation.h"
#include "MaxManaMagnitudeCalculation.generated.h"

UCLASS()
class UMaxManaMagnitudeCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMaxManaMagnitudeCalculation(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition IntelligenceCapture;
	FGameplayEffectAttributeCaptureDefinition LevelCapture;
};
