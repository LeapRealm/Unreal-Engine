#pragma once

#include "GameplayTagContainer.h"

struct FAuraGameplayTags
{
public:
	static FAuraGameplayTags& Get();

public:
	static void InitializeNativeTags();

private:
	void AddInitialTags();
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName);

public:
	// Base
	FGameplayTag Attribute_Base_Level;

	// Vital
	FGameplayTag Attribute_Vital_Health;
	FGameplayTag Attribute_Vital_Mana;

	// Primary
	FGameplayTag Attribute_Primary_Strength;
	FGameplayTag Attribute_Primary_Intelligence;
	FGameplayTag Attribute_Primary_Resilience;
	FGameplayTag Attribute_Primary_Vigor;

	// Secondary
	FGameplayTag Attribute_Secondary_Armor;
	FGameplayTag Attribute_Secondary_ArmorPenetration;
	FGameplayTag Attribute_Secondary_BlockChance;
	FGameplayTag Attribute_Secondary_CriticalHitChance;
	FGameplayTag Attribute_Secondary_CriticalHitDamage;
	FGameplayTag Attribute_Secondary_CriticalHitResistance;
	FGameplayTag Attribute_Secondary_HealthRegeneration;
	FGameplayTag Attribute_Secondary_ManaRegeneration;
	FGameplayTag Attribute_Secondary_MaxHealth;
	FGameplayTag Attribute_Secondary_MaxMana;

	// Resistance
	FGameplayTag Attribute_Resistance_Fire;
	FGameplayTag Attribute_Resistance_Lightning;
	FGameplayTag Attribute_Resistance_Arcane;
	FGameplayTag Attribute_Resistance_Physical;
	
	// Message
	FGameplayTag Message_HealthCrystal;
	FGameplayTag Message_HealthPotion;
	FGameplayTag Message_ManaCrystal;
	FGameplayTag Message_ManaPotion;

	// Input
	FGameplayTag Input_LMB;
	FGameplayTag Input_RMB;
	FGameplayTag Input_1;
	FGameplayTag Input_2;
	FGameplayTag Input_3;
	FGameplayTag Input_4;

	// Event
	FGameplayTag Event_Montage_FireBolt;

	// Damage
	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Arcane;
	FGameplayTag Damage_Physical;
	
	TMap<FGameplayTag, FGameplayTag> DamageTypeToResistance;

	// Effect
	FGameplayTag Effect_HitReact;

	// Ability
	FGameplayTag Ability_Attack;
	FGameplayTag Ability_Summon;
	FGameplayTag Ability_Fire_FireBolt;

	// Cooldown
	FGameplayTag Cooldown_Fire_FireBolt;

	// Combat Socket
	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_LeftHand;
	FGameplayTag CombatSocket_Tail;

	// Montage
	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;

	// Gameplay Cue
	FGameplayTag GameplayCue_MeleeImpact;
};
