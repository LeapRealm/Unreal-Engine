#include "AbilitySystem/GASAbilitySystemComponent.h"

void UGASAbilitySystemComponent::OnSetAbilityActorInto()
{
	OnGameplayEffectAppliedDelegateToSelf.RemoveAll(this);
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UGASAbilitySystemComponent::EffectApplied);
}

void UGASAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec,
	FActiveGameplayEffectHandle EffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(OUT TagContainer);
	EffectAssetTags.Broadcast(TagContainer);
}
