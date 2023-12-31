﻿#include "AuraSceneWidget.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraSceneWidget)

UAuraSceneWidget::UAuraSceneWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UAuraSceneWidget::BindSeparatedAttributeChangedDelegates()
{
	Super::BindSeparatedAttributeChangedDelegates();

	BIND_ATTRIBUTE_CHANGE_SEPARATE_FUNCTION(Health);
	BIND_ATTRIBUTE_CHANGE_SEPARATE_FUNCTION(MaxHealth);
	BIND_ATTRIBUTE_CHANGE_SEPARATE_FUNCTION(Mana);
	BIND_ATTRIBUTE_CHANGE_SEPARATE_FUNCTION(MaxMana);
}

void UAuraSceneWidget::BindCustomDelegates()
{
	Super::BindCustomDelegates();

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->OnEffectApplied_AssetTags.AddLambda([this](const FGameplayTagContainer& AssetTags)
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
