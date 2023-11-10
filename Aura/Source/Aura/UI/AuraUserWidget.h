#pragma once

#include "Blueprint/UserWidget.h"
#include "GameplayEffectTypes.h"
#include "AuraUserWidget.generated.h"

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
	void TryInit(UAbilitySystemComponent* ASC = nullptr);
	
protected:
	virtual void BindDelegates();
	
protected:
	void BindAttributeChangeGeneralFunction(const TArray<FGameplayTag>& Tags);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnAttributeChanged(const FGameplayTag& Tag, float NewValue);
	
private:
	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayTag> WatchingAttributeTags;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<const UAuraAttributeSet> AttributeSet;
};
