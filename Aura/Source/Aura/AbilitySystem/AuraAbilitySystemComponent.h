#pragma once

#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&);

UCLASS()
class UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UAuraAbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void BindEffectAppliedDelegate();
	
protected:
	void OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

public:
	FEffectAssetTags EffectAssetTags;
};
