#pragma once

#include "CoreMinimal.h"
#include "Creature/CreatureBase.h"
#include "Interface/TargetInterface.h"
#include "MonsterBase.generated.h"

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

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> WidgetComponent;
};
