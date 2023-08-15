#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Data/GameData.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChangedStatData, const FGameplayTag&, const FStatData&)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FRAMEWORK_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatComponent();

public:
	void Init(const FGameplayTag& CreatureTag);

	template <typename UserClass, typename FuncType>
	void AddDelegate(const FGameplayTag& StatTag, UserClass* Object, FuncType Func);
	
	FStatData GetStat(const FGameplayTag& StatTag);
	float GetValue(const FGameplayTag& StatTag);
	float GetMinValue(const FGameplayTag& StatTag);
	float GetMaxValue(const FGameplayTag& StatTag);
	
	void AddValue(const FGameplayTag& StatTag, float Value);
	void AddMinValue(const FGameplayTag& StatTag, float Value);
	void AddMaxValue(const FGameplayTag& StatTag, float Value);
	
private:
	TMap<FGameplayTag, FStatData> Stats;
	TMap<FGameplayTag, FOnChangedStatData> Delegates;
};

template <typename UserClass, typename FuncType>
void UStatComponent::AddDelegate(const FGameplayTag& StatTag, UserClass* Object, FuncType Func)
{
	FOnChangedStatData& Delegate = Delegates.FindOrAdd(StatTag);
	Delegate.AddUObject(Object, Func);
	(Object->*Func)(StatTag, GetStat(StatTag));
}
