#pragma once

#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

class UAuraAbilityInfoSet;
struct FAuraAbilityInfoEntry;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEffectApplied_AssetTags, const FGameplayTagContainer&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FAbilityChangedDelegate, bool, const FAuraAbilityInfoEntry&);

UCLASS()
class UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UAuraAbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void BindEffectAppliedDelegate();
	void AddStartupAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	
	void AbilityInputHeld(const FGameplayTag& InputTag);
	void AbilityInputReleased(const FGameplayTag& InputTag);

	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	
public:
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	virtual void OnRemoveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	FAuraAbilityInfoEntry GetAbilityInfoForSpec(const FGameplayAbilitySpec& AbilitySpec);
	void GetAllAbilityInfos(TArray<FAuraAbilityInfoEntry>& OutAbilityInfos);

public:
	void OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

	UFUNCTION(Client, Reliable)
	void Client_OnEffectApplied(const FGameplayTagContainer& TagContainer);

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAuraAbilityInfoSet> AbilityInfoSet;
	
public:
	FOnEffectApplied_AssetTags OnEffectApplied_AssetTags;
	FAbilityChangedDelegate AbilityChangedDelegate;
};
