#pragma once

#include "AbilitySystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

class AAuraPlayerState;
class AAuraPlayerController;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UAuraUserWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category="Cache")
	TObjectPtr<AAuraPlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="Cache")
	TObjectPtr<AAuraPlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="Cache")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="Cache")
	TObjectPtr<const UAttributeSet> AttributeSet;
};
