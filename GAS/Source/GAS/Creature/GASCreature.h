#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GASCreature.generated.h"

UCLASS()
class GAS_API AGASCreature : public ACharacter
{
	GENERATED_BODY()

public:
	AGASCreature();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Combat)
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
