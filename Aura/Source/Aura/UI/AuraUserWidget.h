#pragma once

#include "Blueprint/UserWidget.h"
#include "GameplayEffectTypes.h"
#include "AuraUserWidget.generated.h"

class UAbilitySystemComponent;
class UAuraAttributeSet;

UCLASS()
class UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UAuraUserWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnAttributeChanged(const FGameplayTag& Tag, float NewValue);
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayTag> WatchingAttributes;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<const UAuraAttributeSet> AttributeSet;
};
