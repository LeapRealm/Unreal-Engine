#pragma once

#include "GameplayEffectExecutionCalculation.h"
#include "DamageExecutionCalculation.generated.h"

UCLASS()
class UDamageExecutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UDamageExecutionCalculation(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
