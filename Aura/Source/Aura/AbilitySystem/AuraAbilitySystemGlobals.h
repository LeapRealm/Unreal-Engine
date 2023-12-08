#pragma once

#include "AbilitySystemGlobals.h"
#include "AuraAbilitySystemGlobals.generated.h"

UCLASS()
class UAuraAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	
public:
	UAuraAbilitySystemGlobals(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
