#pragma once

#include "AuraUserWidget.h"
#include "AuraSceneWidget.generated.h"

UCLASS()
class UAuraSceneWidget : public UAuraUserWidget
{
	GENERATED_BODY()
	
public:
	UAuraSceneWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float NewValue);

	UFUNCTION(BlueprintImplementableEvent)
	void OnMaxHealthChanged(float NewValue);

	UFUNCTION(BlueprintImplementableEvent)
	void OnManaChanged(float NewValue);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnMaxManaChanged(float NewValue);
	
private:
	ATTRIBUTE_DELEGATE_FUNCTION(Health);
	ATTRIBUTE_DELEGATE_FUNCTION(MaxHealth);
	ATTRIBUTE_DELEGATE_FUNCTION(Mana);
	ATTRIBUTE_DELEGATE_FUNCTION(MaxMana);
};
