#include "LyraInputConfig.h"

#include "LyraClone/LyraLogChannels.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraInputConfig)

ULyraInputConfig::ULyraInputConfig(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

const UInputAction* ULyraInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	// NativeInputActions를 순회하면서 InputTag에 해당하는 객체가 있는지 체크합니다.
	// 만약 있다면, 해당 InputAction을 반환하고 없다면 nullptr를 반환합니다.
	for (const FLyraInputAction& Action : NativeInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogLyra, Error, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}

const UInputAction* ULyraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FLyraInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogLyra, Error, TEXT("Can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
