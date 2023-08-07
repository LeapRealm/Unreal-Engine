#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "CombatInterface.h"
#include "GASPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class GAS_API AGASPlayerState : public APlayerState, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AGASPlayerState();

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	virtual int32 GetPlayerLevel() override { return Level; }

	UFUNCTION()
	void OnRep_Level(int32 OldValue);
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;
};
