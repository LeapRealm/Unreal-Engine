#pragma once

#include "CoreMinimal.h"
#include "Widget/Widget_Base.h"
#include "Widget_SceneBase.generated.h"

struct FStatData;
struct FGameplayTag;

UCLASS()
class FRAMEWORK_API UWidget_SceneBase : public UWidget_Base
{
	GENERATED_BODY()

public:
	virtual void RefreshUI(const FGameplayTag& StatTag, const FStatData& StatData) override { }
};
