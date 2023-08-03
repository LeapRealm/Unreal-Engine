#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetUnderMouseAbilityTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FGameplayAbilityTargetDataHandle&, Data);

UCLASS()
class GAS_API UTargetDataUnderMouseAbilityTask : public UAbilityTask
{
	GENERATED_BODY()

private:
	virtual void Activate() override;

public:
	UFUNCTION(BlueprintCallable, Category="AbilityTasks", meta=(DisplayName="Get Target Data Under Mouse", HidePin="OwningAbility", DefaultToSelf="OwningAbility", BlueprintInternalUseOnly="true"))
	static UTargetDataUnderMouseAbilityTask* CreateTargetDataUnderMouseAbilityTask(UGameplayAbility* OwningAbility);
	
	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature OnCompleted;

	void SendMouseCursorData();
	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag GameplayTag);
};
