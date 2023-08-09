#include "UIData.h"

#include "..\UI\UI_Base.h"

UClass* UUIData::FindUIClassForTag(const FGameplayTag& UITag)
{
	const TSoftClassPtr<UUI_Base>* ClassPtr = UIClasses.Find(UITag);
	if (ClassPtr == nullptr)
		return nullptr;
	
	return (*ClassPtr).LoadSynchronous();
}
