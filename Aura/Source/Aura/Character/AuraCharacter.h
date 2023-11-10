#pragma once

#include "AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
	
public:
	AAuraCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitDefaultAttributes() const override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Asset|Attribute")
	TSubclassOf<UGameplayEffect> DefaultBaseAttributes;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Asset|Attribute")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Asset|Attribute")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Asset|Attribute")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	
private:
	UPROPERTY(VisibleAnywhere, Category="Component")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Component")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
};
