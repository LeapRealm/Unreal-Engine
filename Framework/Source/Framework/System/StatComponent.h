#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

USTRUCT(BlueprintType)
struct FStatData
{
	GENERATED_BODY()

public:
	FStatData() : BaseValue(0.f), CurrentValue(0.f) { }
	FStatData(float DefaultValue) : BaseValue(DefaultValue), CurrentValue(DefaultValue) { }

	float GetBaseValue() const { return BaseValue; }
	void SetBaseValue(float NewValue) { BaseValue = NewValue; }
	
	float GetCurrentValue() const { return CurrentValue; }
	void SetCurrentValue(float NewValue) { CurrentValue = NewValue; }

public:
	bool operator==(const FStatData& Other) { return (BaseValue == Other.BaseValue) && (CurrentValue == Other.CurrentValue); }
	bool operator!=(const FStatData& Other) { return !(*this == Other); }
	
protected:
	float BaseValue;
	float CurrentValue;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FRAMEWORK_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatComponent();

	// TODO:
	// 스탯 추가 및 삭제
	// 스탯 가져오기
	// 스탯 변경 기능 + 스탯 변경시 수정할 함수 적용(ex.Clamp,OnDead) + 스탯 변경시(이전과 다를시) 델리게이트 알림
	
public:
	// void AddStat(const FGameplayTag& StatTag, const FStatData& InitialStatData, TFunction<void(FStatData& StatData)> ModifyFunc);
	// void RemoveStat(const FGameplayTag& StatTag);
	//
	// FStatData GetStat(const FGameplayTag& StatTag) const;
	// void SetStat(const FGameplayTag& StatTag, const FStatData& NewStatData);
	
private:
	TMap<FGameplayTag, FStatData> StatTagToStatData;
	TMap<FGameplayTag, TFunction<void(FStatData& StatData)>> StatTagToModifyFunc;
};
