#include "WidgetManager.h"

#include "Util/Define.h"
#include "Widget/Popup/Widget_PopupBase.h"
#include "Widget/Scene/Widget_SceneBase.h"

UWidget_PopupBase* UWidgetManager::PeekPopupUI()
{
	if (popupStack.Num() == 0)
		return nullptr;
	return popupStack.Top();
}

void UWidgetManager::ClosePopupUI(UWidget_PopupBase* Popup)
{
	if (popupStack.Num() == 0)
		return;

	if (popupStack.Top() != Popup)
	{
		LOG_ERROR(TEXT("Can't Close Popup"))
		return;
	}

	ClosePopupUI();
}

void UWidgetManager::ClosePopupUI()
{
	if (popupStack.Num() == 0)
		return;

	UWidget_PopupBase* Popup = popupStack.Pop();
	Popup->RemoveFromParent();
	popupOrder--;
}

void UWidgetManager::CloseAllPopupUI()
{
	while (popupStack.Num() > 0)
		ClosePopupUI();
}

void UWidgetManager::Clear()
{
	CloseAllPopupUI();

	if (SceneUI)
	{
		SceneUI->RemoveFromParent();
		SceneUI = nullptr;
	}
}
