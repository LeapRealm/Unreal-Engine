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
	UPROPERTY(EditAnywhere)
	float Value = 0.f;

	UPROPERTY(EditAnywhere)
	float MinValue = 0.f;

	UPROPERTY(EditAnywhere)
	float MaxValue = 0.f;
};

UCLASS()
class FRAMEWORK_API UGameData : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE const TMap<FGameplayTag, FStatData>& GetInitialStats() const { return InitialStats; }
	
private:
	TMap<FGameplayTag, FStatData> InitialStats;
};
