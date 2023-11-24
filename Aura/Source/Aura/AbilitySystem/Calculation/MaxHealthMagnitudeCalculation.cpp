#include "MaxHealthMagnitudeCalculation.h"

#include "AbilitySystem/AuraAttributeSet.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(MaxHealthMagnitudeCalculation)

UMaxHealthMagnitudeCalculation::UMaxHealthMagnitudeCalculation(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    VigorCapture.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorCapture.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorCapture.bSnapshot = false;
	RelevantAttributesToCapture.Add(VigorCapture);
	
	LevelCapture.AttributeToCapture = UAuraAttributeSet::GetLevelAttribute();
	LevelCapture.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	LevelCapture.bSnapshot = false;
	RelevantAttributesToCapture.Add(LevelCapture);
}

float UMaxHealthMagnitudeCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorCapture, Spec, EvaluateParameters, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.f);

	float Level = 0.f;
	GetCapturedAttributeMagnitude(LevelCapture, Spec, EvaluateParameters, Level);
	Level = FMath::Max<float>(Level, 1.f);

	return 80.f + (2.5f * Vigor) + (10.f * Level);
}
