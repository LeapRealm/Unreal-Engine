﻿#pragma once

#include "Blueprint/UserWidget.h"
#include "GameplayEffectTypes.h"
#include "AuraUserWidget.generated.h"

struct FAuraAbilityInfoEntry;
class UAbilitySystemComponent;
class UAuraAttributeSet;

#define BIND_ATTRIBUTE_CHANGE_SEPARATE_FUNCTION(PropertyName)		\
	On##PropertyName##Changed(AttributeSet->Get##PropertyName());	\
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->Get##PropertyName##Attribute()).AddLambda([this](const FOnAttributeChangeData& Data){ On##PropertyName##Changed(Data.NewValue); });

UCLASS()
class UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UAuraUserWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UFUNCTION(BlueprintCallable)
	void Init(UAbilitySystemComponent* ASC = nullptr);
	
protected:
	void AddWatchingAttributeTags(const TArray<FGameplayTag>& Tags);
	
	void BindAttributeChangedDelegates();
	void BindUnitedAttributeChangedDelegates();
	virtual void BindSeparatedAttributeChangedDelegates();
	
	void BindAbilityChangedDelegate();
	
	virtual void BindCustomDelegates();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnAttributeChanged(const FGameplayTag& Tag, float NewValue);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnAbilityChanged(bool bGiven, const FAuraAbilityInfoEntry& AbilityInfo);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FGameplayTag> WatchingAttributeTags;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<const UAuraAttributeSet> AttributeSet;
};
