#include "AuraHUD.h"

#include "AuraUserWidget.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraHUD)

AAuraHUD::AAuraHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void AAuraHUD::Init()
{
	check(OverlayWidgetClass);
	
	OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->AddToViewport();
}
