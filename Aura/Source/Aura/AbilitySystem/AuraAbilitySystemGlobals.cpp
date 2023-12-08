#include "AuraAbilitySystemGlobals.h"

#include "AuraAbilityTypes.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraAbilitySystemGlobals)

UAuraAbilitySystemGlobals::UAuraAbilitySystemGlobals(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

FGameplayEffectContext* UAuraAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAuraGameplayEffectContext();
}
