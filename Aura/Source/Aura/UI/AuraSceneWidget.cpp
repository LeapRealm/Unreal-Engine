#include "AuraSceneWidget.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraSceneWidget)

UAuraSceneWidget::UAuraSceneWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void UAuraSceneWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ThisClass::OnMaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetManaAttribute()).AddUObject(this, &ThisClass::OnManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxManaAttribute()).AddUObject(this, &ThisClass::OnMaxManaChanged);

	OnHealthChanged(AttributeSet->GetHealth());
	OnMaxHealthChanged(AttributeSet->GetMaxHealth());
	OnManaChanged(AttributeSet->GetMana());
	OnMaxManaChanged(AttributeSet->GetMaxMana());
}
