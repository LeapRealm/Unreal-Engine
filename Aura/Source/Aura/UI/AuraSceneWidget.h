﻿#pragma once

#include "AuraUserWidget.h"
#include "AuraSceneWidget.generated.h"

USTRUCT(BlueprintType)
struct FMessageWidgetRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

UCLASS()
class UAuraSceneWidget : public UAuraUserWidget
{
	GENERATED_BODY()
	
public:
	UAuraSceneWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BindSeparatedAttributeChangedDelegates() override;
	virtual void BindCustomDelegates() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float NewValue);

	UFUNCTION(BlueprintImplementableEvent)
	void OnMaxHealthChanged(float NewValue);

	UFUNCTION(BlueprintImplementableEvent)
	void OnManaChanged(float NewValue);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnMaxManaChanged(float NewValue);
	
	UFUNCTION(BlueprintImplementableEvent)
	void DisplayMessage(const FMessageWidgetRow& Row);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UAuraUserWidget> AttributeWidget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Asset|Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
};
