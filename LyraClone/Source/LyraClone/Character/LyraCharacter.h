#pragma once

#include "ModularCharacter.h"
#include "LyraCharacter.generated.h"

class ULyraCameraComponent;
class ULyraPawnExtensionComponent;

UCLASS()
class ALyraCharacter : public AModularCharacter
{
	GENERATED_BODY()
	
public:
	ALyraCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Lyra|Character")
	TObjectPtr<ULyraPawnExtensionComponent> PawnExtensionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Lyra|Character")
	TObjectPtr<ULyraCameraComponent> CameraComponent;
};
