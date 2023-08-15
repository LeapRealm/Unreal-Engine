#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "GameData.generated.h"

USTRUCT(BlueprintType)
struct FStatData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	float Value = 0.f;

	UPROPERTY(EditDefaultsOnly)
	float MinValue = 0.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxValue = 0.f;
};

USTRUCT(BlueprintType)
struct FInitialStatData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FStatData> InitialStats;
};

UCLASS()
class FRAMEWORK_API UGameData : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE const FInitialStatData& FindInitialStat(const FGameplayTag& CreatureTag) const { return CreatureInitialStats.FindChecked(CreatureTag); }
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, FInitialStatData> CreatureInitialStats;
};
