#include "BTTask_Attack.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AIController.h"
#include "AuraGameplayTags.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/EnemyInterface.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(BTTask_Attack)

UBTTask_Attack::UBTTask_Attack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    AttackTag = FAuraGameplayTags::Get().Ability_Attack;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIController = Cast<AAIController>(OwnerComp.GetOwner()))
	{
		if (APawn* ControlledPawn = AIController->GetPawn())
		{
			if (AActor* CombatTarget = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(CombatTargetSelector.SelectedKeyName)))
			{
				IEnemyInterface::Execute_SetCombatTarget(ControlledPawn, CombatTarget);
			}
			
			if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(ControlledPawn))
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(AttackTag);
				ASC->TryActivateAbilitiesByTag(TagContainer, true);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	
	return EBTNodeResult::Failed;
}
