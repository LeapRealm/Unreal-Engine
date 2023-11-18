﻿#pragma once

#include "GameplayTagContainer.h"
#include "LyraInputConfig.generated.h"

class UInputAction;

// GameplayTag와 InputAction을 연결하는 레퍼 구조체
USTRUCT(BlueprintType)
struct FLyraInputAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UInputAction> InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ExposeFunctionCategories="InputTag"))
	FGameplayTag InputTag;
};

// 활성화 가능한 InputAction들을 가지고 있는 클래스
UCLASS(BlueprintType)
class ULyraInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	ULyraInputConfig(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty="InputAction"))
	TArray<FLyraInputAction> NativeInputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty="InputAction"))
	TArray<FLyraInputAction> AbilityInputActions;
};
