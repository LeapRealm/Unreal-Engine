#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CombatInterface.h"
#include "GASCreature.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class GAS_API AGASCreature : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AGASCreature();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void InitAbilityActorInfo() { }
	
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	void InitializeDefaultAttributes();
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GamePlayEffectClass, float Level);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Combat)
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Attributes)
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Attributes)
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Attributes)
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

public:
	void AddCharacterAbilities();
	
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	virtual FVector GetCombatSocketLocation() override;

	UPROPERTY(EditAnywhere, Category="Combat")
	FName WeaponTipSocketName;
};
