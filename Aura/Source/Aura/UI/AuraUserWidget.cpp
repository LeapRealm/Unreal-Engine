#include "AuraUserWidget.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraUserWidget)

UAuraUserWidget::UAuraUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UAuraUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	IAbilitySystemInterface* AbilitySystemInterface = GetOwningPlayerPawn<IAbilitySystemInterface>();
	check(AbilitySystemInterface);
	
	AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();
	check(AbilitySystemComponent);
	
	AttributeSet = Cast<UAuraAttributeSet>(AbilitySystemComponent->GetAttributeSet(UAuraAttributeSet::StaticClass()));
	check(AttributeSet);
}
