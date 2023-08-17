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
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	void MoveKeyboard(const FInputActionValue& Value);
	
	void LeftMousePressed(const FInputActionValue& Value);
	void LeftMouseHeld(const FInputActionValue& Value);
	void LeftMouseReleased(const FInputActionValue& Value);
	
	void HoldPressed() { bHoldKeyDown = true; }
	void HoldReleased() { bHoldKeyDown = false; }
	
	void HighlightTrace();
	void AutoMoving();

private:
	float PressTime = 0.f;
	float PressThreshold = 0.5;
	float AutoRunAcceptanceRadius = 50.f;
	
	bool bHoldKeyDown = false;
	bool bAutoMoving = false;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AActor> TargetActor;
	
	ITargetInterface* HighlightActor;
	FVector TargetLocation = FVector::ZeroVector;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> MoveKeyboardAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> LeftMouseAction;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> HoldAction;
};
