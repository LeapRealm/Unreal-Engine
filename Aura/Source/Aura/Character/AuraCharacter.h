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

public:
	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<USpringArmComponent> SpringArm;
};
