#pragma once

#include "CoreMinimal.h"
#include "Creature/CreatureBase.h"
#include "PlayerBase.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class FRAMEWORK_API APlayerBase : public ACreatureBase
{
	GENERATED_BODY()

public:
	APlayerBase();

public:
	virtual void PostInitializeComponents() override;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;
};
