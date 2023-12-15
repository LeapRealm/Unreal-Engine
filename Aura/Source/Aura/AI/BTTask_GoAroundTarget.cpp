#include "BTTask_GoAroundTarget.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(BTTask_GoAroundTarget)

UBTTask_GoAroundTarget::UBTTask_GoAroundTarget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

EBTNodeResult::Type UBTTask_GoAroundTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AActor* Actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target.SelectedKeyName)))
	{
		if (UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld()))
		{
			FNavLocation RandomLocation;
			if (NavSystem->GetRandomPointInNavigableRadius(Actor->GetActorLocation(), Radius, RandomLocation))
			{
				if (UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent())
				{
					BlackboardComponent->SetValueAsVector(NewLocation.SelectedKeyName, RandomLocation.Location);
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
