#include "AuraGameplayTags.h"

#include "GameplayTagsManager.h"

FAuraGameplayTags& FAuraGameplayTags::Get()
{
	static FAuraGameplayTags GameplayTags;
	return GameplayTags; 
}

void FAuraGameplayTags::InitializeNativeTags()
{
	Get().AddInitialTags();
}

void FAuraGameplayTags::AddInitialTags()
{
	// Base
	AddTag(Attribute_Base_Level,							"Attribute.Base.Level",							"Attribute Base Level");

	// Vital
	AddTag(Attribute_Vital_Health,						"Attribute.Vital.Health",						"Attribute Vital Health");
	AddTag(Attribute_Vital_Mana,							"Attribute.Vital.Mana",							"Attribute Vital Mana");

	// Primary
	AddTag(Attribute_Primary_Strength,					"Attribute.Primary.Strength",					"Attribute Primary Strength");
	AddTag(Attribute_Primary_Intelligence,				"Attribute.Primary.Intelligence",				"Attribute Primary Intelligence");
	AddTag(Attribute_Primary_Resilience,					"Attribute.Primary.Resilience",					"Attribute Primary Resilience");
	AddTag(Attribute_Primary_Vigor,						"Attribute.Primary.Vigor",						"Attribute Primary Vigor");

	// Secondary
	AddTag(Attribute_Secondary_Armor,					"Attribute.Secondary.Armor",					"Attribute Secondary Armor");
	AddTag(Attribute_Secondary_ArmorPenetration,			"Attribute.Secondary.ArmorPenetration",			"Attribute Secondary ArmorPenetration");
	AddTag(Attribute_Secondary_BlockChance,				"Attribute.Secondary.BlockChance",				"Attribute Secondary BlockChance");
	AddTag(Attribute_Secondary_CriticalHitChange,		"Attribute.Secondary.CriticalHitChange",		"Attribute Secondary CriticalHitChange");
	AddTag(Attribute_Secondary_CriticalHitDamage,		"Attribute.Secondary.CriticalHitDamage",		"Attribute Secondary CriticalHitDamage");
	AddTag(Attribute_Secondary_CriticalHitResistance,	"Attribute.Secondary.CriticalHitResistance",	"Attribute Secondary CriticalHitResistance");
	AddTag(Attribute_Secondary_HealthRegeneration,		"Attribute.Secondary.HealthRegeneration",		"Attribute Secondary HealthRegeneration");
	AddTag(Attribute_Secondary_ManaRegeneration,			"Attribute.Secondary.ManaRegeneration",			"Attribute Secondary ManaRegeneration");
	AddTag(Attribute_Secondary_MaxHealth,				"Attribute.Secondary.MaxHealth",				"Attribute Secondary MaxHealth");
	AddTag(Attribute_Secondary_MaxMana,					"Attribute.Secondary.MaxMana",					"Attribute Secondary MaxMana");

	// Message
	AddTag(Message_HealthCrystal,						"Message.HealthCrystal",						"Message HealthCrystal");
	AddTag(Message_HealthPotion,							"Message.HealthPotion",							"Message HealthPotion");
	AddTag(Message_ManaCrystal,							"Message.ManaCrystal",							"Message ManaCrystal");
	AddTag(Message_ManaPotion,							"Message.ManaPotion",							"Message ManaPotion");
}

void FAuraGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}
