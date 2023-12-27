#include "BTTask_Attack_Elemental.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AIController.h"
#include "AuraGameplayTags.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/CombatInterface.h"
#include "Interface/EnemyInterface.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(BTTask_Attack_Elemental)

UBTTask_Attack_Elemental::UBTTask_Attack_Elemental(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    AttackTag = FAuraGameplayTags::Get().Ability_Attack;
	SummonTag = FAuraGameplayTags::Get().Ability_Summon;
}

EBTNodeResult::Type UBTTask_Attack_Elemental::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIController = Cast<AAIController>(OwnerComp.GetOwner()))
	{
		if (APawn* ControlledPawn = AIController->GetPawn())
		{
			if (AActor* CombatTarget = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(CombatTargetSelector.SelectedKeyName)))
			{
				IEnemyInterface::Execute_SetCombatTarget(ControlledPawn, CombatTarget);
				int32 MinionCount = ICombatInterface::Execute_GetMinionCount(ControlledPawn);
				if (MinionCount < MinionSpawnThreshold)
				{
					AbilityTag = SummonTag;
				}
				else
				{
					AbilityTag = AttackTag;
				}
			}
			
			if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(ControlledPawn))
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(AbilityTag);
				ASC->TryActivateAbilitiesByTag(TagContainer, true);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
