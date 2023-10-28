#pragma once

#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

UCLASS(Abstract)
class AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()
	
public:
	AAuraCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
