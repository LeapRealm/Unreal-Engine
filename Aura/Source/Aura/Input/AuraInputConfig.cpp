#include "AuraInputConfig.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraInputConfig)

UAuraInputConfig::UAuraInputConfig(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

const UInputAction* UAuraInputConfig::FindInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	if (const TObjectPtr<UInputAction>* InputAction = TagToInputAction.Find(InputTag))
	{
		return *InputAction;
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find InputAction for InputTag [%s] on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}
	
	return nullptr;
}
