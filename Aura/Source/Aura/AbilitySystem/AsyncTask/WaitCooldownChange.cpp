#include "WaitCooldownChange.h"

#include "AbilitySystemComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(WaitCooldownChange)

UWaitCooldownChange::UWaitCooldownChange(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

UWaitCooldownChange* UWaitCooldownChange::WaitForCooldownChange(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& CooldownTag)
{
	UWaitCooldownChange* WaitCooldownChange = NewObject<UWaitCooldownChange>();
	WaitCooldownChange->ASC = AbilitySystemComponent;
	WaitCooldownChange->CooldownTag = CooldownTag;

	if (IsValid(AbilitySystemComponent) == false || CooldownTag.IsValid() == false)
	{
		WaitCooldownChange->EndTask();
		return nullptr;
	}

	AbilitySystemComponent->RegisterGameplayTagEvent(CooldownTag, EGameplayTagEventType::NewOrRemoved).AddUObject(WaitCooldownChange, &ThisClass::CooldownTagChanged);
	WaitCooldownChange->EffectAddedDelegateHandle = AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(WaitCooldownChange, &ThisClass::OnActiveEffectAdded);
	
	return WaitCooldownChange;
}

void UWaitCooldownChange::EndTask()
{
	if (ASC.IsValid() == false)
		return;

	ASC->RegisterGameplayTagEvent(CooldownTag, EGameplayTagEventType::NewOrRemoved).RemoveAll(this);
	ASC->OnActiveGameplayEffectAddedDelegateToSelf.Remove(EffectAddedDelegateHandle);
	
	SetReadyToDestroy();
	MarkAsGarbage();
}

void UWaitCooldownChange::CooldownTagChanged(const FGameplayTag InCooldownTag, int32 NewCount)
{
	if (NewCount == 0)
	{
		CooldownEnd.Broadcast(0.f);
	}
}

void UWaitCooldownChange::OnActiveEffectAdded(UAbilitySystemComponent* TargetASC, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer AssetTags;
	SpecApplied.GetAllAssetTags(AssetTags);

	FGameplayTagContainer GrantedTags;
	SpecApplied.GetAllGrantedTags(GrantedTags);
	
	if (AssetTags.HasTagExact(CooldownTag) || GrantedTags.HasTagExact(CooldownTag))
	{
		FGameplayEffectQuery GameplayEffectQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTag.GetSingleTagContainer());
		TArray<float> TimeRemains = ASC->GetActiveEffectsTimeRemaining(GameplayEffectQuery);
		if (TimeRemains.Num() > 0)
		{
			float TimeRemaining = TimeRemains[0];
			for (int32 i = 1; i < TimeRemains.Num(); i++)
			{
				if (TimeRemains[i] > TimeRemaining)
				{
					TimeRemaining = TimeRemains[i];
				}
			}
			CooldownStart.Broadcast(TimeRemaining);
		}
	}
}
