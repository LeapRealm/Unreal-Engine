#pragma once

#include "CoreMinimal.h"
#include "Creature/CreatureBase.h"
#include "Interface/TargetInterface.h"
#include "MonsterBase.generated.h"

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Idle,
	Patrol,
	Chase,
	Attack,
};

class UWidgetComponent;

UCLASS()
class FRAMEWORK_API AMonsterBase : public ACreatureBase, public ITargetInterface
{
	GENERATED_BODY()

public:
	AMonsterBase();
	
public:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	
public:
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	virtual void OnDead(const FGameplayTag& StatTag, const FStatData& StatData) override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> WidgetComponent;
		
	UPROPERTY(VisibleAnywhere)
	EMonsterState State = EMonsterState::Idle;
};
