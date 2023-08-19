#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

class APlayerBase;

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Search,
	Chase,
	Attack,
	Dead,
};

UCLASS()
class FRAMEWORK_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	void TickSearch(float DeltaSeconds);
	void TickChase(float DeltaSeconds);
	void TickAttack(float DeltaSeconds);
	void TickDead(float DeltaSeconds);

	bool Find360Target();
	bool Find180Target();

private:
	void Attack();

public:
	void SetState(EMonsterState NewState);

private:
	EMonsterState State = EMonsterState::Search;
	FTimerHandle SearchHandle;

	float SearchDistance = 800.f;
	float AttackDistance = 150.f;
	
	float TargetSearchDuration = 0.5f;
	float CurrSearchDuration = 0.f;

	float TargetAttackDuration = 1.5f;
	float CurrAttackDuration = 0.f;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<APlayerBase> TargetPlayer;
};
