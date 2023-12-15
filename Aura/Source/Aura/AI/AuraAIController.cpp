#include "AuraAIController.h"

#include "BehaviorTree/BlackboardComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraAIController)

AAuraAIController::AAuraAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
}
