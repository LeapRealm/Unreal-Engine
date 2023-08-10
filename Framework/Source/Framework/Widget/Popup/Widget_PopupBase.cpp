#include "Widget_PopupBase.h"

#include "Manager/WidgetManager.h"
#include "Util/Util.h"

void UWidget_PopupBase::NativeConstruct()
{
	Super::NativeConstruct();

	RefreshUI();
}

void UWidget_PopupBase::ClosePopupUI()
{
	UUtil::GetUIManager(this)->ClosePopupUI(this);
}
