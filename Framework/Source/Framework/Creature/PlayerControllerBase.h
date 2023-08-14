#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class ITargetInterface;

UCLASS()
class FRAMEWORK_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

private:
	void MoveKeyboard(const FInputActionValue& Value);
	
	void MoveMousePressed(const FInputActionValue& Value);
	void MoveMouseHeld(const FInputActionValue& Value);
	void MoveMouseReleased(const FInputActionValue& Value);
	
	void HoldPressed() { bHoldKeyDown = true; }
	void HoldReleased() { bHoldKeyDown = false; }

	void TickCursorTrace();
	void AutoRunning();

private:
	FVector Destination = FVector::ZeroVector;
	bool bHoldKeyDown = false;
	bool bAutoRunning = false;
	float PressTime = 0.f;
	float ShortPressThreshold = 0.5;
	TObjectPtr<ITargetInterface> TargetActor;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> MoveKeyboardAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> MoveMouseAction;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> HoldAction;
};
