#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Base.generated.h"

UCLASS()
class FRAMEWORK_API UUI_Base : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void RefreshUI() { }
};
