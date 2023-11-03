#include "AuraSceneWidget.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraSceneWidget)

UAuraSceneWidget::UAuraSceneWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
    WatchingAttributes.Append({
    	GameplayTags.Attribute_Vital_Health,
    	GameplayTags.Attribute_Vital_Mana,
    	GameplayTags.Attribute_Secondary_MaxHealth,
    	GameplayTags.Attribute_Secondary_MaxMana,
    });
}

void UAuraSceneWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda([this](const FGameplayTagContainer& AssetTags)
	{
		for (const FGameplayTag& Tag : AssetTags)
		{
			FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
			if (Tag.MatchesTag(MessageTag))
			{
				const FMessageWidgetRow* Row = MessageWidgetDataTable->FindRow<FMessageWidgetRow>(Tag.GetTagName(), TEXT(""));
				DisplayMessage(*Row);
			}
		}
	});
}
