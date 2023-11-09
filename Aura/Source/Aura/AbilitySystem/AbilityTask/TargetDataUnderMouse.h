#pragma once

#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FGameplayAbilityTargetDataHandle&, TargetDataHandle);

UCLASS()
class UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UTargetDataUnderMouse(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UFUNCTION(BlueprintCallable, Category="Ability|Task", meta=(DisplayName = "TargetDataUnderMouse", HidePin="OwningAbility", DefaultToSelf="OwningAbility", BlueprintInternalUseOnly="true"))
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);
	
	virtual void Activate() override;

protected:
	void SendTargetData();
	void ReceiveTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTag ActivationTag);

protected:
	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature OnTargetFound;
};
