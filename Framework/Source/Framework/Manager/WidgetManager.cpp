#include "WidgetManager.h"

#include "Util/Define.h"
#include "Widget/Popup/Widget_PopupBase.h"
#include "Widget/Scene/Widget_SceneBase.h"

UWidget_PopupBase* UWidgetManager::PeekPopupWidget()
{
	if (popupStack.Num() == 0)
		return nullptr;
	return popupStack.Top();
}

void UWidgetManager::ClosePopupWidget(UWidget_PopupBase* Popup)
{
	if (popupStack.Num() == 0)
		return;

	if (popupStack.Top() != Popup)
	{
		LOG_ERROR(TEXT("Can't Close Popup Widget"))
		return;
	}

	ClosePopupWidget();
}

void UWidgetManager::ClosePopupWidget()
{
	if (popupStack.Num() == 0)
		return;

	UWidget_PopupBase* Popup = popupStack.Pop();
	Popup->RemoveFromParent();
	popupOrder--;
}

void UWidgetManager::CloseAllPopupWidget()
{
	while (popupStack.Num() > 0)
		ClosePopupWidget();
}

void UWidgetManager::Clear()
{
	CloseAllPopupWidget();

	if (SceneWidget)
	{
		SceneWidget->RemoveFromParent();
		SceneWidget = nullptr;
	}
}
