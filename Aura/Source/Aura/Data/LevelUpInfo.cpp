#include "LevelUpInfo.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LevelUpInfo)

ULevelUpInfo::ULevelUpInfo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

int32 ULevelUpInfo::FindLevelForXP(int32 XP)
{
	int32 Level = 1;
	bool bSearching = true;

	while (bSearching)
	{
		if (LevelUpInfos.Num() - 1 <= Level)
			return Level;

		if (XP >= LevelUpInfos[Level].LevelUpRequirement)
		{
			Level++;
		}
		else
		{
			bSearching = false;
		}
	}
	return Level;
}
