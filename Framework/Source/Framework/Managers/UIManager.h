#pragma once

#include "CoreMinimal.h"
#include "DataManager.h"
#include "Data/UIData.h"
#include "Utils/Define.h"
#include "Utils/Util.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "UI/Scene/UI_SceneBase.h"
#include "UIManager.generated.h"

class UUI_Base;
class UUI_SceneBase;
class UUI_PopupBase;

UCLASS()
class FRAMEWORK_API UUIManager : public UObject
{
	GENERATED_BODY()

public:
	template<typename T>
	T* ShowSceneUI(const FGameplayTag& UITag);

	template<typename T>
	T* ShowPopupUI(const FGameplayTag& UITag);
	
	UUI_PopupBase* PeekPopupUI();
	void ClosePopupUI(UUI_PopupBase* Popup);
	void ClosePopupUI();
	void CloseAllPopupUI();
	void Clear();

private:
	UPROPERTY(VisibleAnywhere)
	int32 popupOrder = 1;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UUI_SceneBase> SceneUI;
	
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<UUI_PopupBase>> popupStack;
};

template <typename T>
T* UUIManager::ShowSceneUI(const FGameplayTag& UITag)
{
	if (UITag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild UI Tag"));
		return nullptr;
	}

	UUIData* UIData = UUtil::GetDataManager(this)->GetUIData();
	const UClass* UIClass = UIData->FindUIClassForTag(UITag);
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
T* UUIManager::ShowPopupUI(const FGameplayTag& UITag)
{
	if (UITag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild UI Tag"));
		return nullptr;
	}

	UUIData* UIData = UUtil::GetDataManager(this)->GetUIData();
	UClass* UIClass = UIData->FindUIClassForTag(UITag);
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
