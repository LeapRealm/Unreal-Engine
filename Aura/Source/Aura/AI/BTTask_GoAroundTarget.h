#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GoAroundTarget.generated.h"

UCLASS()
class UBTTask_GoAroundTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_GoAroundTarget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FBlackboardKeySelector NewLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FBlackboardKeySelector Target;

	UPROPERTY(EditAnywhere)
	float Radius = 300.f;
};
