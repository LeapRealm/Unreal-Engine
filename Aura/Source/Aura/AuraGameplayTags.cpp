#include "AuraGameplayTags.h"

#include "GameplayTagsManager.h"

FAuraGameplayTags& FAuraGameplayTags::Get()
{
	static FAuraGameplayTags GameplayTags;
	return GameplayTags; 
}

void FAuraGameplayTags::InitializeNativeTags()
{
	AddTag(Attribute_Vital_Health,			"Attribute.Vital.Health",			"Attribute Vital Health");
	AddTag(Attribute_Vital_MaxHealth,		"Attribute.Vital.MaxHealth",		"Attribute Vital MaxHealth");
	AddTag(Attribute_Vital_Mana,				"Attribute.Vital.Mana",				"Attribute Vital Mana");
	AddTag(Attribute_Vital_MaxMana,			"Attribute.Vital.MaxMana",			"Attribute Vital MaxMana");
	
	AddTag(Attribute_Primary_Intelligence,	"Attribute.Primary.Intelligence",	"Attribute Primary Intelligence");
	AddTag(Attribute_Primary_Resilience,		"Attribute.Primary.Resilience",		"Attribute Primary Resilience");
	AddTag(Attribute_Primary_Strength,		"Attribute.Primary.Strength",		"Attribute Primary Strength");
	AddTag(Attribute_Primary_Vigor,			"Attribute.Primary.Vigor",			"Attribute Primary Vigor");

	AddTag(Message_HealthCrystal,			"Message.HealthCrystal",			"Message HealthCrystal");
	AddTag(Message_HealthPotion,				"Message.HealthPotion",				"Message HealthPotion");
	AddTag(Message_ManaCrystal,				"Message.ManaCrystal",				"Message ManaCrystal");
	AddTag(Message_ManaPotion,				"Message.ManaPotion",				"Message ManaPotion");
}

void FAuraGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}
