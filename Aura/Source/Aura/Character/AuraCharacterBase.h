#pragma once

#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AAuraCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

public:
	virtual void InitAbilityActorInfo();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }
	virtual UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
protected:
	UPROPERTY(VisibleAnywhere, Category="Component")
	TObjectPtr<USkeletalMeshComponent> WeaponMeshComponent;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
