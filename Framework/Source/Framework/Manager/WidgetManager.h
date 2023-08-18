#pragma once

#include "CoreMinimal.h"
#include "DataManager.h"
#include "Util/Define.h"
#include "Util/Util.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "Widget/Scene/Widget_SceneBase.h"
#include "WidgetManager.generated.h"

class UWidget_Base;
class UWidget_SceneBase;
class UWidget_PopupBase;

UCLASS()
class FRAMEWORK_API UWidgetManager : public UObject
{
	GENERATED_BODY()

public:
	template<typename T>
	T* ShowSceneWidget(const FGameplayTag& WidgetTag);

	template<typename T>
	T* ShowPopupWidget(const FGameplayTag& WidgetTag);
	
	UWidget_PopupBase* PeekPopupWidget();
	void ClosePopupWidget(UWidget_PopupBase* Popup);
	void ClosePopupWidget();
	void CloseAllPopupWidget();
	void Clear();

private:
	UPROPERTY(VisibleAnywhere)
	int32 popupOrder = 1;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidget_SceneBase> SceneWidget;
	
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<UWidget_PopupBase>> popupStack;
};

template <typename T>
T* UWidgetManager::ShowSceneWidget(const FGameplayTag& WidgetTag)
{
	if (WidgetTag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild Widget Tag"));
		return nullptr;
	}
	
	TSubclassOf<UUserWidget> WidgetClass = UUtil::GetDataManager(this)->FindWidgetClassForTag(WidgetTag);
	if (WidgetClass == nullptr)
	{
		LOG_ERROR(TEXT("Can't Find Widget Class on Asset Data"));
		return nullptr;
	}

	T* Widget = CreateWidget<T>(GetWorld(), WidgetClass);
	Widget->AddToViewport(0);
	SceneWidget = Widget;

	return Widget;
}

template <typename T>
T* UWidgetManager::ShowPopupWidget(const FGameplayTag& WidgetTag)
{
	if (WidgetTag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild Widget Tag"));
		return nullptr;
	}

	TSubclassOf<UUserWidget> WidgetClass = UUtil::GetDataManager(this)->FindWidgetClassForTag(WidgetTag);
	if (WidgetClass == nullptr)
	{
		LOG_ERROR(TEXT("Can't Find Widget Class on Asset Data"));
		return nullptr;
	}

	T* Widget = CreateWidget<T>(GetWorld(), TSubclassOf<T>(WidgetClass));
	Widget->AddToViewport(popupOrder++);
	popupStack.Push(Widget);

	return Widget;
}
