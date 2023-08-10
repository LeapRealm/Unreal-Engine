#pragma once

#include "CoreMinimal.h"
#include "UI/UI_Base.h"
#include "UI_PopupBase.generated.h"

UCLASS()
class FRAMEWORK_API UUI_PopupBase : public UUI_Base
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void RefreshUI() override { }
	virtual void ClosePopupUI();
};
