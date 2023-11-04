#pragma once

#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEffectAssetTags, const FGameplayTagContainer&);

UCLASS()
class UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UAuraAbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void BindEffectAppliedDelegate();
	void AddStartupAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	
protected:
	void OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

public:
	FOnEffectAssetTags OnEffectAssetTags;
};
