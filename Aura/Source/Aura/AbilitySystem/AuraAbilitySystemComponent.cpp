#include "AuraAbilitySystemComponent.h"

#include "Ability/AuraGameplayAbility.h"
#include "Data/AuraAbilityInfo.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraAbilitySystemComponent)

UAuraAbilitySystemComponent::UAuraAbilitySystemComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    static ConstructorHelpers::FObjectFinder<UAuraAbilityInfoSet> DA_AbilityInfoSet(TEXT("/Script/Aura.AuraAbilityInfoSet'/Game/Data/DA_AbilityInfoSet.DA_AbilityInfoSet'"));
	if (DA_AbilityInfoSet.Succeeded())
	{
		AbilityInfoSet = DA_AbilityInfoSet.Object;
	}
}

void UAuraAbilitySystemComponent::BindEffectAppliedDelegate()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::OnEffectApplied);
}

void UAuraAbilitySystemComponent::AddStartupAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1.f);
		if (const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->InputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::GetAbilityInfos(TArray<FAuraAbilityInfoEntry>& OutAbilityInfos)
{
	OutAbilityInfos.Empty();
	
	ABILITYLIST_SCOPE_LOCK();
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		FAuraAbilityInfoEntry AbilityInfo = AbilityInfoSet->FindAbilityInfoForTag(UAuraAbilitySystemComponent::GetAbilityTagFromSpec(AbilitySpec));
		if (AbilityInfo.AbilityTag.IsValid())
		{
			AbilityInfo.InputTag = UAuraAbilitySystemComponent::GetInputTagFromSpec(AbilitySpec);
			OutAbilityInfos.Add(AbilityInfo);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputHeld(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid() == false)
		return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (AbilitySpec.IsActive() == false)
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputReleased(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid() == false)
		return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

FGameplayTag UAuraAbilitySystemComponent::GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	if (AbilitySpec.Ability)
	{
		for (const FGameplayTag& Tag : AbilitySpec.Ability->AbilityTags)
		{
			if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Ability"))))
			{
				return Tag;
			}
		}
	}
	return FGameplayTag();
}

FGameplayTag UAuraAbilitySystemComponent::GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	for (const FGameplayTag& Tag : AbilitySpec.DynamicAbilityTags)
	{
		if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Input"))))
		{
			return Tag;
		}
	}
	return FGameplayTag();
}

void UAuraAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	TArray<FAuraAbilityInfoEntry> AbilityInfos;
	GetAbilityInfos(AbilityInfos);
	AbilityChangedDelegate.Broadcast(AbilityInfos);
}

void UAuraAbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	
	if (TagContainer.IsEmpty() == false)
	{
		Client_OnEffectApplied(TagContainer);
	}
}

void UAuraAbilitySystemComponent::Client_OnEffectApplied_Implementation(const FGameplayTagContainer& TagContainer)
{
	OnEffectApplied_AssetTags.Broadcast(TagContainer);
}
