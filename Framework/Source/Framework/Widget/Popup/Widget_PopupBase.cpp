#include "Widget_PopupBase.h"

#include "Manager/WidgetManager.h"
#include "Util/Util.h"

void UWidget_PopupBase::ClosePopupUI()
{
	UUtil::GetWidgetManager(this)->ClosePopupWidget(this);
}
