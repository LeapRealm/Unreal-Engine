#include "UI/HUD/GASHUD.h"

#include "AttributeMenuWidgetController.h"
#include "UI/Controller/OverlayWidgetController.h"
#include "UI/Widget/GASUserWidget.h"

void AGASHUD::BeginPlay()
{
	Super::BeginPlay();
}

UOverlayWidgetController* AGASHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetControllerRef == nullptr)
	{
		OverlayWidgetControllerRef = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetControllerRef->SetWidgetControllerParams(WCParams);
		OverlayWidgetControllerRef->BindCallbacksToDependencies();
	}

	return OverlayWidgetControllerRef;
}

UAttributeMenuWidgetController* AGASHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetControllerRef == nullptr)
	{
		AttributeMenuWidgetControllerRef = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetControllerRef->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetControllerRef->BindCallbacksToDependencies();
	}

	return AttributeMenuWidgetControllerRef;
}

void AGASHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	check(OverlayWidgetClass);
	check(OverlayWidgetControllerClass);
	
	UGASUserWidget* Widget = CreateWidget<UGASUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
	OverlayWidgetRef = Widget;

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidgetRef->SetWidgetController(WidgetController);

	WidgetController->BroadcastInitialValues();
}
