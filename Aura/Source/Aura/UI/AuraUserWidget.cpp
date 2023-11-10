#include "AuraUserWidget.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
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
	
	BindDelegates();
}

void UAuraUserWidget::BindDelegates()
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

void UAuraUserWidget::BindAttributeChangeGeneralFunction(const TArray<FGameplayTag>& Tags)
{
	WatchingAttributeTags.Append(Tags);
}
