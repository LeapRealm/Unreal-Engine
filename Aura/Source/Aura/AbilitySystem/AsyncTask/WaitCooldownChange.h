#pragma once

#include "ActiveGameplayEffectHandle.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "WaitCooldownChange.generated.h"

struct FGameplayEffectSpec;
class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCooldownChangeSignature, float, TimeRemaining);

UCLASS(BlueprintType, meta=(ExposedAsyncProxy="AsyncTask"))
class UWaitCooldownChange : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	UWaitCooldownChange(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"))
	static UWaitCooldownChange* WaitForCooldownChange(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& CooldownTag);

	UFUNCTION(BlueprintCallable)
	void EndTask();

	void CooldownTagChanged(const FGameplayTag InCooldownTag, int32 NewCount);
	void OnActiveEffectAdded(UAbilitySystemComponent* TargetASC, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveEffectHandle);

public:
	UPROPERTY(BlueprintAssignable)
	FCooldownChangeSignature CooldownStart;

	UPROPERTY(BlueprintAssignable)
	FCooldownChangeSignature CooldownEnd;

public:
	UPROPERTY()
	TWeakObjectPtr<UAbilitySystemComponent> ASC;

	FGameplayTag CooldownTag;
	FDelegateHandle EffectAddedDelegateHandle;
};
