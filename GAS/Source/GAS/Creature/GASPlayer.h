#pragma once

#include "CoreMinimal.h"
#include "Creature/GASCreature.h"
#include "GASPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class GAS_API AGASPlayer : public AGASCreature
{
	GENERATED_BODY()

public:
	AGASPlayer();

protected:
	UPROPERTY(EditAnywhere, Category=Camera)
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(EditAnywhere, Category=Camera)
	TObjectPtr<UCameraComponent> FollowCamera;
};
