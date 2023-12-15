#pragma once

#include "AIController.h"
#include "AuraAIController.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class AAuraAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAuraAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
