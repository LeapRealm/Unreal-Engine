#pragma once

#include "CoreMinimal.h"
#include "DataManager.h"
#include "Data/WidgetData.h"
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
	T* ShowSceneUI(const FGameplayTag& UITag);

	template<typename T>
	T* ShowPopupUI(const FGameplayTag& UITag);
	
	UWidget_PopupBase* PeekPopupUI();
	void ClosePopupUI(UWidget_PopupBase* Popup);
	void ClosePopupUI();
	void CloseAllPopupUI();
	void Clear();

private:
	UPROPERTY(VisibleAnywhere)
	int32 popupOrder = 1;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidget_SceneBase> SceneUI;
	
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<UWidget_PopupBase>> popupStack;
};

template <typename T>
T* UWidgetManager::ShowSceneUI(const FGameplayTag& UITag)
{
	if (UITag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild UI Tag"));
		return nullptr;
	}

	UWidgetData* UIData = UUtil::GetDataManager(this)->GetWidgetData();
	const UClass* UIClass = UIData->FindWidgetClassForTag(UITag);
	if (UIClass == nullptr)
	{
		LOG_ERROR(TEXT("Can't Find UI Class on UI Data"));
		return nullptr;
	}

	T* Widget = CreateWidget<T>(GetWorld(), UIClass);
	Widget->AddToViewport(0);
	SceneUI = Widget;

	return Widget;
}

template <typename T>
T* UWidgetManager::ShowPopupUI(const FGameplayTag& UITag)
{
	if (UITag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild UI Tag"));
		return nullptr;
	}

	UWidgetData* UIData = UUtil::GetDataManager(this)->GetWidgetData();
	UClass* UIClass = UIData->FindWidgetClassForTag(UITag);
	if (UIClass == nullptr)
	{
		LOG_ERROR(TEXT("Can't Find UI Class on UI Data"));
		return nullptr;
	}

	T* Widget = CreateWidget<T>(GetWorld(), TSubclassOf<T>(UIClass));
	Widget->AddToViewport(popupOrder++);
	popupStack.Push(Widget);

	return Widget;
}
