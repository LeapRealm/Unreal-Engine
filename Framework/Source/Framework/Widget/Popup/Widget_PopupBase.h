#pragma once

#include "CoreMinimal.h"
#include "Widget/Widget_Base.h"
#include "Widget_PopupBase.generated.h"

UCLASS()
class FRAMEWORK_API UWidget_PopupBase : public UWidget_Base
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void RefreshUI() override { }
	virtual void ClosePopupUI();
};
