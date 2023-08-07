#pragma once

#include "CoreMinimal.h"
#include "OverlayWidgetController.h"
#include "Creature/GASCreature.h"
#include "Interface/TargetInterface.h"
#include "GASMonster.generated.h"

class UWidgetComponent;

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

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
};
