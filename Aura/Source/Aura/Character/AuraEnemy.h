#pragma once
#include "AuraCharacterBase.h"
#include "Interface/HighlightInterface.h"

#include "AuraEnemy.generated.h"

UCLASS()
class AAuraEnemy : public AAuraCharacterBase, public IHighlightInterface
{
	GENERATED_BODY()
	
public:
	AAuraEnemy(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

public:
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
};
