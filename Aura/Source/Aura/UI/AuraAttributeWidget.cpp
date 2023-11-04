#include "AuraAttributeWidget.h"

#include "AuraGameplayTags.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraAttributeWidget)

UAuraAttributeWidget::UAuraAttributeWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
    BindAttributeChangeGeneralFunction({
    	GameplayTags.Attribute_Primary_Strength,
		GameplayTags.Attribute_Primary_Intelligence,
		GameplayTags.Attribute_Primary_Resilience,
		GameplayTags.Attribute_Primary_Vigor,
		GameplayTags.Attribute_Secondary_Armor,
		GameplayTags.Attribute_Secondary_ArmorPenetration,
		GameplayTags.Attribute_Secondary_BlockChance,
		GameplayTags.Attribute_Secondary_CriticalHitChange,
		GameplayTags.Attribute_Secondary_CriticalHitDamage,
		GameplayTags.Attribute_Secondary_CriticalHitResistance,
		GameplayTags.Attribute_Secondary_HealthRegeneration,
		GameplayTags.Attribute_Secondary_ManaRegeneration,
		GameplayTags.Attribute_Secondary_MaxHealth,
		GameplayTags.Attribute_Secondary_MaxMana,
    });
}
