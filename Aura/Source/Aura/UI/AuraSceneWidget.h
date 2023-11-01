#pragma once

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
	virtual void NativeConstruct() override;

protected:
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
	
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
	void DisplayMessage(FMessageWidgetRow Row);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DataTable")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
};

template <typename T>
T* UAuraSceneWidget::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
