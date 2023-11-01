﻿#pragma once

#include "Blueprint/UserWidget.h"
#include "GameplayEffectTypes.h"
#include "AuraUserWidget.generated.h"

class UAbilitySystemComponent;
class UAuraAttributeSet;

#define BIND_ATTRIBUTE_CHANGE_DELEGATE(PropertyName) AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->Get##PropertyName##Attribute()).AddLambda([this](const FOnAttributeChangeData& Data){ On##PropertyName##Changed(Data.NewValue); });

UCLASS()
class UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UAuraUserWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<const UAuraAttributeSet> AttributeSet;
};
