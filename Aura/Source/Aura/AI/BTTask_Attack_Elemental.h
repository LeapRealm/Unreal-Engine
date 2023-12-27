#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack_Elemental.generated.h"

UCLASS()
class UBTTask_Attack_Elemental : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Attack_Elemental(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	FGameplayTag AbilityTag;
	FGameplayTag AttackTag;
	FGameplayTag SummonTag;

	UPROPERTY(EditAnywhere)
	int32 MinionSpawnThreshold = 2;
	
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector CombatTargetSelector;

};
