#include "MaxManaMagnitudeCalculation.h"

#include "AbilitySystem/AuraAttributeSet.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(MaxManaMagnitudeCalculation)

UMaxManaMagnitudeCalculation::UMaxManaMagnitudeCalculation(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	IntelligenceCapture.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceCapture.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceCapture.bSnapshot = false;
	RelevantAttributesToCapture.Add(IntelligenceCapture);
	
	LevelCapture.AttributeToCapture = UAuraAttributeSet::GetLevelAttribute();
	LevelCapture.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	LevelCapture.bSnapshot = false;
	RelevantAttributesToCapture.Add(LevelCapture);
}

float UMaxManaMagnitudeCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceCapture, Spec, EvaluateParameters, Intelligence);
	Intelligence = FMath::Max<float>(Intelligence, 0.f);

	float Level = 0.f;
	GetCapturedAttributeMagnitude(LevelCapture, Spec, EvaluateParameters, Level);
	Level = FMath::Max<float>(Level, 1.f);

	return 50.f + (2.5f * Intelligence) + (15.f * Level);
}
