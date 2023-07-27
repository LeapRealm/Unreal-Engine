#pragma once

#include "CoreMinimal.h"
#include "Creature/GASCreature.h"
#include "Interface/TargetInterface.h"
#include "GASMonster.generated.h"

UCLASS()
class GAS_API AGASMonster : public AGASCreature, public ITargetInterface
{
	GENERATED_BODY()

public:
	AGASMonster();

	virtual void BeginPlay() override;
	
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	virtual void InitAbilityActorInfo() override;

	virtual int32 GetPlayerLevel() override { return Level; }
	
protected:
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character")
	int32 Level = 1;
};
