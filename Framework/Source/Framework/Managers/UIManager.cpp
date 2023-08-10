#include "Managers/UIManager.h"

#include "UI/Popup/UI_PopupBase.h"

UUI_PopupBase* UUIManager::PeekPopupUI()
{
	if (popupStack.Num() == 0)
		return nullptr;
	return popupStack.Top();
}

void UUIManager::ClosePopupUI(UUI_PopupBase* Popup)
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

void UUIManager::ClosePopupUI()
{
	if (popupStack.Num() == 0)
		return;

	UUI_PopupBase* Popup = popupStack.Pop();
	Popup->RemoveFromParent();
	popupOrder--;
}

void UUIManager::CloseAllPopupUI()
{
	while (popupStack.Num() > 0)
		ClosePopupUI();
}

void UUIManager::Clear()
{
	CloseAllPopupUI();

	if (SceneUI)
	{
		SceneUI->RemoveFromParent();
		SceneUI = nullptr;
	}
}
