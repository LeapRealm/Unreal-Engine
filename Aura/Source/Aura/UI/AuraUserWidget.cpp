#include "AuraUserWidget.h"

#include "AbilitySystemGlobals.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Player/AuraPlayerState.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraUserWidget)

UAuraUserWidget::UAuraUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UAuraUserWidget::Init(UAbilitySystemComponent* ASC)
{
	if (IsValid(ASC) == false || IsValid(AbilitySystemComponent))
		return;
	
	AbilitySystemComponent = ASC;
	check(AbilitySystemComponent);
	
	AttributeSet = Cast<UAuraAttributeSet>(AbilitySystemComponent->GetAttributeSet(UAuraAttributeSet::StaticClass()));
	check(AttributeSet);

	BindAttributeChangedDelegates();
	BindAbilityChangedDelegate();
	BindCustomDelegates();
}

void UAuraUserWidget::AddWatchingAttributeTags(const TArray<FGameplayTag>& Tags)
{
	WatchingAttributeTags.Append(Tags);
}

void UAuraUserWidget::BindAttributeChangedDelegates()
{
	BindUnitedAttributeChangedDelegates();
	BindSeparatedAttributeChangedDelegates();
}

void UAuraUserWidget::BindUnitedAttributeChangedDelegates()
{
	for (const FGameplayTag& Tag : WatchingAttributeTags)
	{
		if (auto AttributeFunc = AttributeSet->TagToAttributeFunc.Find(Tag))
		{
			const FGameplayAttribute& Attribute = (*AttributeFunc)(); 
			OnAttributeChanged(Tag, Attribute.GetNumericValue(AttributeSet));
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddLambda([this, Tag](const FOnAttributeChangeData& Data)
			{
				OnAttributeChanged(Tag, Data.NewValue);
			});
		}
	}
}

void UAuraUserWidget::BindSeparatedAttributeChangedDelegates()
{
	
}

void UAuraUserWidget::BindAbilityChangedDelegate()
{
	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		TArray<FAuraAbilityInfoEntry> AbilityInfos;
		AuraASC->GetAllAbilityInfos(AbilityInfos);
		for (const FAuraAbilityInfoEntry& AbilityInfo : AbilityInfos)
		{
			OnAbilityChanged(true, AbilityInfo);
		}
		AuraASC->AbilityChangedDelegate.AddUObject(this, &ThisClass::OnAbilityChanged);
	}
}

void UAuraUserWidget::BindCustomDelegates()
{
	
}
