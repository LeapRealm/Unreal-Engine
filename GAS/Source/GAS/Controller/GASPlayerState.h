#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GASPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class GAS_API AGASPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGASPlayerState();

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;
};
