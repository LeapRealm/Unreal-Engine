#pragma once

#include "LevelUpInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraLevelUpInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 LevelUpRequirement = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 AttributePointAward = 1;

	UPROPERTY(EditDefaultsOnly)
	int32 SpellPointAward = 1;
};

UCLASS()
class ULevelUpInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	ULevelUpInfo(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	int32 FindLevelForXP(int32 XP);

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FAuraLevelUpInfo> LevelUpInfos;
};
