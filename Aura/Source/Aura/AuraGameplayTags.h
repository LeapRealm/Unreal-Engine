#pragma once

#include "GameplayTagContainer.h"

struct FAuraGameplayTags
{
public:
	static FAuraGameplayTags& Get();

public:
	void InitializeNativeTags();

private:
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

public:
	FGameplayTag Attribute_Vital_Health;
	FGameplayTag Attribute_Vital_MaxHealth;
	FGameplayTag Attribute_Vital_Mana;
	FGameplayTag Attribute_Vital_MaxMana;

	FGameplayTag Attribute_Primary_Intelligence;
	FGameplayTag Attribute_Primary_Resilience;
	FGameplayTag Attribute_Primary_Strength;
	FGameplayTag Attribute_Primary_Vigor;

	FGameplayTag Message_HealthCrystal;
	FGameplayTag Message_HealthPotion;
	FGameplayTag Message_ManaCrystal;
	FGameplayTag Message_ManaPotion;
};
