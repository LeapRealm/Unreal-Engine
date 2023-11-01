#include "AuraUserWidget.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystem/AuraAttributeSet.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraUserWidget)

UAuraUserWidget::UAuraUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UAuraUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwningPlayerPawn());
	check(AbilitySystemComponent);
	
	AttributeSet = Cast<UAuraAttributeSet>(AbilitySystemComponent->GetAttributeSet(UAuraAttributeSet::StaticClass()));
	check(AttributeSet);
}
