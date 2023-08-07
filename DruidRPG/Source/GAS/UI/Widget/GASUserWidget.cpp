#include "UI/Widget/GASUserWidget.h"

void UGASUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	OnSetWidgetController();
}
