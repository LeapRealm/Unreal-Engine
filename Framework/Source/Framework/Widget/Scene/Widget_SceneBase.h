#pragma once

#include "CoreMinimal.h"
#include "Widget/Widget_Base.h"
#include "Widget_SceneBase.generated.h"

UCLASS()
class FRAMEWORK_API UWidget_SceneBase : public UWidget_Base
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void RefreshUI() override { }
};
