#pragma once

#include "BehaviorTree/BTService.h"
#include "BTService_FindNearestPlayer.generated.h"

UCLASS()
class UBTService_FindNearestPlayer : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_FindNearestPlayer(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBlackboardKeySelector TargetToFollowSelector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBlackboardKeySelector DistanceToTargetSelector;
};
