#include "UI_PopupBase.h"

#include "Managers/UIManager.h"
#include "Utils/Util.h"

void UUI_PopupBase::NativeConstruct()
{
	Super::NativeConstruct();

	RefreshUI();
}

void UUI_PopupBase::ClosePopupUI()
{
	UUtil::GetUIManager(this)->ClosePopupUI(this);
}
