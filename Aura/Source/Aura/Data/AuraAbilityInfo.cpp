#include "AuraAbilityInfo.h"

#include "AuraLogChannels.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraAbilityInfo)

UAuraAbilityInfoSet::UAuraAbilityInfoSet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

FAuraAbilityInfoEntry UAuraAbilityInfoSet::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for (const FAuraAbilityInfoEntry& AbilityInfo : AbilityInfos)
	{
		if (AbilityInfo.AbilityTag == AbilityTag)
		{
			return AbilityInfo;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("Can't find info for AbilityTag [%s] on AbilityInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
	}

	return FAuraAbilityInfoEntry();
}
