#include "AuraGameplayTags.h"

#include "GameplayTagsManager.h"

FAuraGameplayTags& FAuraGameplayTags::Get()
{
	static FAuraGameplayTags GameplayTags;
	return GameplayTags; 
}

void FAuraGameplayTags::InitializeNativeTags()
{
	AddTag(Attribute_Health,		"Attribute.Health",		"Attribute_Health");
	AddTag(Attribute_MaxHealth,	"Attribute.MaxHealth",	"Attribute_MaxHealth");
	AddTag(Attribute_Mana,		"Attribute.Mana",		"Attribute_Mana");
	AddTag(Attribute_MaxMana,	"Attribute.MaxMana",	"Attribute_MaxMana");
}

void FAuraGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}
