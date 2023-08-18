#pragma once

#include "CoreMinimal.h"
#include "Widget/Scene/Widget_SceneBase.h"
#include "Widget_Scene.generated.h"

class UProgressBar;

UCLASS()
class FRAMEWORK_API UWidget_Scene : public UWidget_SceneBase
{
	GENERATED_BODY()

public:
	virtual void RefreshUI(const FGameplayTag& StatTag, const FStatData& StatData) override;

private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> ManaBar;
};
