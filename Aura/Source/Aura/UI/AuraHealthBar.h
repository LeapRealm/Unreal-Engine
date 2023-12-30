#pragma once

#include "AuraUserWidget.h"
#include "AuraHealthBar.generated.h"

UCLASS()
class UAuraHealthBar : public UAuraUserWidget
{
	GENERATED_BODY()
	
public:
	UAuraHealthBar(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BindSeparatedAttributeChangedDelegates() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float NewValue);

	UFUNCTION(BlueprintImplementableEvent)
	void OnMaxHealthChanged(float NewValue);
};
