#include "AuraAbilitySystemComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraAbilitySystemComponent)

UAuraAbilitySystemComponent::UAuraAbilitySystemComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void UAuraAbilitySystemComponent::BindEffectAppliedDelegate()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::OnEffectApplied);
}

void UAuraAbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}
