#pragma once

#include "AuraUserWidget.h"
#include "AuraSceneWidget.generated.h"

class UAuraAttributeWidget;

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
	UFUNCTION(BlueprintImplementableEvent)
	void DisplayMessage(const FMessageWidgetRow& Row);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UAuraAttributeWidget> AttributeWidget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
};
