#include "System/StatComponent.h"

#include "Manager/DataManager.h"
#include "Util/Define.h"
#include "Util/Util.h"

UStatComponent::UStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UStatComponent::Init(const FGameplayTag& CreatureTag)
{
	if (CreatureTag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild CreatureTag"));
		return;
	}

	const FInitialStatData& InitialStatData = UUtil::GetDataManager(this)->FindInitialStat(CreatureTag);
	Stats = InitialStatData.InitialStats;
}

FStatData UStatComponent::GetStat(const FGameplayTag& StatTag)
{
	if (StatTag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild StatTag"));
		return FStatData();
	}

	const FStatData* StatData = Stats.Find(StatTag);
	if (StatData == nullptr)
	{
		LOG_ERROR(TEXT("Can't find StatData for StatTag"))
		return FStatData();
	}

	return (*StatData);
}

float UStatComponent::GetValue(const FGameplayTag& StatTag)
{
	return GetStat(StatTag).Value;
}

float UStatComponent::GetMinValue(const FGameplayTag& StatTag)
{
	return GetStat(StatTag).MinValue;
}

float UStatComponent::GetMaxValue(const FGameplayTag& StatTag)
{
	return GetStat(StatTag).MaxValue;
}

void UStatComponent::AddValue(const FGameplayTag& StatTag, float Value)
{
	if (StatTag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild StatTag"));
		return;
	}

	FStatData* StatData = Stats.Find(StatTag);
	if (StatData == nullptr)
	{
		LOG_ERROR(TEXT("Can't find StatData for StatTag"))
		return;
	}

	StatData->Value = FMath::Clamp(StatData->Value + Value, StatData->MinValue, StatData->MaxValue);
	
	if (FOnChangedStatData* OnChangedStatData = Delegates.Find(StatTag))
		(*OnChangedStatData).Broadcast(StatTag, (*StatData));
}

void UStatComponent::AddMinValue(const FGameplayTag& StatTag, float Value)
{
	if (StatTag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild StatTag"));
		return;
	}

	FStatData* StatData = Stats.Find(StatTag);
	if (StatData == nullptr)
	{
		LOG_ERROR(TEXT("Can't find StatData for StatTag"))
		return;
	}

	StatData->MinValue = FMath::Clamp(StatData->MinValue + Value, FLT_MIN, StatData->MaxValue);
	StatData->Value = FMath::Max(StatData->MinValue, StatData->Value);

	if (FOnChangedStatData* OnChangedStatData = Delegates.Find(StatTag))
		(*OnChangedStatData).Broadcast(StatTag, (*StatData));
}

void UStatComponent::AddMaxValue(const FGameplayTag& StatTag, float Value)
{
	if (StatTag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild StatTag"));
		return;
	}

	FStatData* StatData = Stats.Find(StatTag);
	if (StatData == nullptr)
	{
		LOG_ERROR(TEXT("Can't find StatData for StatTag"))
		return;
	}

	StatData->MaxValue = FMath::Clamp(StatData->MaxValue + Value, StatData->MinValue, FLT_MAX);
	StatData->Value = FMath::Min(StatData->Value, StatData->MaxValue);
	
	if (FOnChangedStatData* OnChangedStatData = Delegates.Find(StatTag))
		(*OnChangedStatData).Broadcast(StatTag, (*StatData));
}
