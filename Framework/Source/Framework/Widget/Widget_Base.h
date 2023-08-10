#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Base.generated.h"

UCLASS()
class FRAMEWORK_API UWidget_Base : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void RefreshUI() { }
};
