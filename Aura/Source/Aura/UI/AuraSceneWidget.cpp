#include "AuraSceneWidget.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraSceneWidget)

UAuraSceneWidget::UAuraSceneWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void UAuraSceneWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BIND_ATTRIBUTE_CHANGE_DELEGATE(Health);
	BIND_ATTRIBUTE_CHANGE_DELEGATE(MaxHealth);
	BIND_ATTRIBUTE_CHANGE_DELEGATE(Mana);
	BIND_ATTRIBUTE_CHANGE_DELEGATE(MaxMana);

	OnHealthChanged(AttributeSet->GetHealth());
	OnMaxHealthChanged(AttributeSet->GetMaxHealth());
	OnManaChanged(AttributeSet->GetMana());
	OnMaxManaChanged(AttributeSet->GetMaxMana());

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda([this](const FGameplayTagContainer& AssetTags)
	{
		for (const FGameplayTag& Tag : AssetTags)
		{
			FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
			if (Tag.MatchesTag(MessageTag))
			{
				const FMessageWidgetRow* Row = GetDataTableRowByTag<FMessageWidgetRow>(MessageWidgetDataTable, Tag);
				DisplayMessage(*Row);
			}
		}
	});
}
