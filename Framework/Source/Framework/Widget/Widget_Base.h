#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Base.generated.h"

struct FStatData;
struct FGameplayTag;

UCLASS()
class FRAMEWORK_API UWidget_Base : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void RefreshUI(const FGameplayTag& StatTag, const FStatData& StatData) { }
};
