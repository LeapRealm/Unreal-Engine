#include "UI/Controller/OverlayWidgetController.h"

#include "GASAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	const UGASAttributeSet* GASAttributeSet = CastChecked<UGASAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(GASAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(GASAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(GASAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(GASAttributeSet->GetMaxMana());
}
