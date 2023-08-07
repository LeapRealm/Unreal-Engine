#include "AbilitySystem/Data/AttributeInfo.h"

FGASAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound)
{
	for (const FGASAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
			return Info;
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find info for Attribute Tag [%s]"), *AttributeTag.ToString());
	}

	return FGASAttributeInfo();
}
