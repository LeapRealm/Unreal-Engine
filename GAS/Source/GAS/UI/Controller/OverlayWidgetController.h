#pragma once

#include "CoreMinimal.h"
#include "UI/Controller/GASWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewValue);

UCLASS(BlueprintType, Blueprintable)
class GAS_API UOverlayWidgetController : public UGASWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;
    	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;
};
