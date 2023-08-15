#pragma once

#include "CoreMinimal.h"
#include "Widget/Widget_Base.h"
#include "Widget_Nameplate.generated.h"

struct FStatData;
struct FGameplayTag;
class UProgressBar;

UCLASS()
class FRAMEWORK_API UWidget_Nameplate : public UWidget_Base
{
	GENERATED_BODY()

public:
	virtual void RefreshUI(const FGameplayTag& StatTag, const FStatData& StatData) override;
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
};
