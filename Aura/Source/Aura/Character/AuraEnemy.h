#pragma once

#include "AuraCharacterBase.h"
#include "GameplayTagContainer.h"
#include "Data/CharacterClassInfo.h"
#include "..\Interface\EnemyInterface.h"

#include "AuraEnemy.generated.h"

class AAuraAIController;
class UBehaviorTree;

UCLASS()
class AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AAuraEnemy(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitDefaultAttributes() const override;
	virtual void PossessedBy(AController* NewController) override;

public:
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;

private:
	void HitReactTagChanged(const FGameplayTag Tag, int32 NewCount);
	virtual void Death() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECharacterClass CharacterClass = ECharacterClass::None;

	UPROPERTY(BlueprintReadOnly)
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly)
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float LifeSpan = 5.f;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> CombatTarget;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;
};
