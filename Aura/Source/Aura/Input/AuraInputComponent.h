#pragma once

#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraInputComponent.generated.h"

class UAuraInputConfig;

UCLASS()
class UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	UAuraInputComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);

	for (const auto& Tuple : InputConfig->TagToInputAction)
	{
		const FGameplayTag& Tag = Tuple.Key;
		const UInputAction* InputAction = Tuple.Value;
		if (Tag.IsValid() && InputAction)
		{
			if (PressedFunc)
			{
				BindAction(InputAction, ETriggerEvent::Started, Object, PressedFunc, Tag);
			}

			if (ReleasedFunc)
			{
				BindAction(InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Tag);
			}

			if (HeldFunc)
			{
				BindAction(InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Tag);
			}
		}
	}
}
