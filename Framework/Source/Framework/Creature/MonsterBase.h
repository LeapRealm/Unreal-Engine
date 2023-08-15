#pragma once

#include "CoreMinimal.h"
#include "Creature/CreatureBase.h"
#include "Interface/TargetInterface.h"
#include "MonsterBase.generated.h"

UCLASS()
class FRAMEWORK_API AMonsterBase : public ACreatureBase, public ITargetInterface
{
	GENERATED_BODY()

public:
	AMonsterBase();
	
public:
	virtual void PostInitializeComponents() override;
	
public:
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
};
