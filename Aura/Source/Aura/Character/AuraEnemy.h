#pragma once

#include "AuraCharacterBase.h"
#include "GameplayTagContainer.h"
#include "Data/CharacterClassInfo.h"
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
	virtual void InitAbilityActorInfo() override;
	virtual void InitDefaultAttributes() const override;

public:
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

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
};
