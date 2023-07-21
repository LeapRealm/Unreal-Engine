#include "AbilitySystem/GASAttributeSet.h"

#include "Net/UnrealNetwork.h"

UGASAttributeSet::UGASAttributeSet()
{
	// TODO: TEMP
	InitHealth(80.f);
	InitMaxHealth(100.f);
	InitMana(40.f);
	InitMaxMana(100.f);
}

void UGASAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UGASAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, Health, OldValue);
}

void UGASAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, MaxHealth, OldValue);
}

void UGASAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, Mana, OldValue);
}

void UGASAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, MaxMana, OldValue);
}
