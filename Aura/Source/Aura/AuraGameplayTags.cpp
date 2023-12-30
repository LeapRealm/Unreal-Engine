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
	AddTag(Attribute_Base_Level,							"Attribute.Base.Level");

	// Vital
	AddTag(Attribute_Vital_Health,						"Attribute.Vital.Health");
	AddTag(Attribute_Vital_Mana,							"Attribute.Vital.Mana");							

	// Primary
	AddTag(Attribute_Primary_Strength,					"Attribute.Primary.Strength");
	AddTag(Attribute_Primary_Intelligence,				"Attribute.Primary.Intelligence");
	AddTag(Attribute_Primary_Resilience,					"Attribute.Primary.Resilience");
	AddTag(Attribute_Primary_Vigor,						"Attribute.Primary.Vigor");

	// Secondary
	AddTag(Attribute_Secondary_Armor,					"Attribute.Secondary.Armor");
	AddTag(Attribute_Secondary_ArmorPenetration,			"Attribute.Secondary.ArmorPenetration");
	AddTag(Attribute_Secondary_BlockChance,				"Attribute.Secondary.BlockChance");
	AddTag(Attribute_Secondary_CriticalHitChance,		"Attribute.Secondary.CriticalHitChance");
	AddTag(Attribute_Secondary_CriticalHitDamage,		"Attribute.Secondary.CriticalHitDamage");
	AddTag(Attribute_Secondary_CriticalHitResistance,	"Attribute.Secondary.CriticalHitResistance");
	AddTag(Attribute_Secondary_HealthRegeneration,		"Attribute.Secondary.HealthRegeneration");
	AddTag(Attribute_Secondary_ManaRegeneration,			"Attribute.Secondary.ManaRegeneration");
	AddTag(Attribute_Secondary_MaxHealth,				"Attribute.Secondary.MaxHealth");
	AddTag(Attribute_Secondary_MaxMana,					"Attribute.Secondary.MaxMana");

	// Resistance
	AddTag(Attribute_Resistance_Fire,					"Attribute.Resistance.Fire");
	AddTag(Attribute_Resistance_Lightning,				"Attribute.Resistance.Lightning");
	AddTag(Attribute_Resistance_Arcane,					"Attribute.Resistance.Arcane");
	AddTag(Attribute_Resistance_Physical,				"Attribute.Resistance.Physical");
	
	// Message
	AddTag(Message_HealthCrystal,						"Message.HealthCrystal");
	AddTag(Message_HealthPotion,							"Message.HealthPotion");
	AddTag(Message_ManaCrystal,							"Message.ManaCrystal");
	AddTag(Message_ManaPotion,							"Message.ManaPotion");

	// Input
	AddTag(Input_LMB,									"Input.LMB");
	AddTag(Input_RMB,									"Input.RMB");
	AddTag(Input_1,										"Input.1");
	AddTag(Input_2,										"Input.2");
	AddTag(Input_3,										"Input.3");
	AddTag(Input_4,										"Input.4");

	// Event
	AddTag(Event_Montage_FireBolt,						"Event.Montage.FireBolt");
	
	// Damage
	AddTag(Damage,										"Damage");
	AddTag(Damage_Fire,									"Damage.Fire");
	AddTag(Damage_Lightning,								"Damage.Lightning");
	AddTag(Damage_Arcane,								"Damage.Arcane");
	AddTag(Damage_Physical,								"Damage.Physical");
	
	// Map of DamageType to Resistance
	DamageTypeToResistance.Add(Damage_Fire,			Attribute_Resistance_Fire);
	DamageTypeToResistance.Add(Damage_Lightning,	Attribute_Resistance_Lightning);
	DamageTypeToResistance.Add(Damage_Arcane,		Attribute_Resistance_Arcane);
	DamageTypeToResistance.Add(Damage_Physical,		Attribute_Resistance_Physical);
	
	// Effect
	AddTag(Effect_HitReact,								"Effect.HitReact");

	// Ability
	AddTag(Ability_Attack,								"Ability.Attack");
	AddTag(Ability_Summon,								"Ability.Summon");
	AddTag(Ability_Fire_FireBolt,						"Ability.Fire.FireBolt");

	// Combat Socket
	AddTag(CombatSocket_Weapon,							"CombatSocket.Weapon");
	AddTag(CombatSocket_RightHand,						"CombatSocket.RightHand");
	AddTag(CombatSocket_LeftHand,						"CombatSocket.LeftHand");
	AddTag(CombatSocket_Tail,							"CombatSocket.Tail");

	// Montage
	AddTag(Montage_Attack_1,								"Montage.Attack.1");
	AddTag(Montage_Attack_2,								"Montage.Attack.2");
	AddTag(Montage_Attack_3,								"Montage.Attack.3");
	AddTag(Montage_Attack_4,								"Montage.Attack.4");

	// Gameplay Cue
	AddTag(GameplayCue_MeleeImpact,						"GameplayCue.MeleeImpact");
}

void FAuraGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagName));
}
