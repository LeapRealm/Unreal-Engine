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
	FGameplayTag Attribute_Health;
	FGameplayTag Attribute_MaxHealth;
	FGameplayTag Attribute_Mana;
	FGameplayTag Attribute_MaxMana;
};
