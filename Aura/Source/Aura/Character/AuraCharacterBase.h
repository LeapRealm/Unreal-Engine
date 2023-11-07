#pragma once

#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
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

protected:
	virtual void InitAbilityActorInfo();
	void InitDefaultAttributes() const;

public:
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }
	virtual UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	void AddStartupAbilities();
	
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Asset|Attribute")
	TSubclassOf<UGameplayEffect> DefaultBaseAttributes;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Asset|Attribute")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Asset|Attribute")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Asset|Attribute")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	
protected:
	UPROPERTY(EditAnywhere, Category="Asset|Ability")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
protected:
	UPROPERTY(VisibleAnywhere, Category="Component")
	TObjectPtr<USkeletalMeshComponent> WeaponMeshComponent;

	UPROPERTY(VisibleAnywhere, Category="Component")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;
};
