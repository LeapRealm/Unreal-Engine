#include "System/StatComponent.h"

#include "Manager/DataManager.h"
#include "Util/Util.h"
#include "Util/Define.h"

UStatComponent::UStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	LoadStats();
}

FOnChangedStatData& UStatComponent::GetDelegate(const FGameplayTag& StatTag)
{
	return Delegates.FindOrAdd(StatTag);
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
		(*OnChangedStatData).Broadcast((*StatData));
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
		(*OnChangedStatData).Broadcast((*StatData));
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
		(*OnChangedStatData).Broadcast((*StatData));
}

void UStatComponent::LoadStats()
{
	Stats = UUtil::GetDataManager(this)->GetInitialStats();
}
