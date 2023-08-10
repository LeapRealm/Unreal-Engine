#include "WidgetData.h"

#include "Widget/Widget_Base.h"

UClass* UWidgetData::FindWidgetClassForTag(const FGameplayTag& UITag)
{
	const TSoftClassPtr<UWidget_Base>* ClassPtr = WidgetClasses.Find(UITag);
	if (ClassPtr == nullptr)
		return nullptr;
	
	return (*ClassPtr).LoadSynchronous();
}
