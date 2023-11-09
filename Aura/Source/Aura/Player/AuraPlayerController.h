#pragma once

#include "AuraPlayerController.generated.h"

class USplineComponent;
class UAuraAbilitySystemComponent;
struct FGameplayTag;
class IHighlightInterface;
class UInputAction;
class UInputMappingContext;
class UAuraInputConfig;
struct FInputActionValue;

UCLASS()
class AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

private:
	void CursorTrace();
	void AutoRun();
	
	void Move(const FInputActionValue& Value);

	void ShiftPressed() { bShiftKeyDown = true; }
	void ShiftReleased() { bShiftKeyDown = false; }
	
	void AbilityInputPressed(FGameplayTag InputTag);
	void AbilityInputHeld(FGameplayTag InputTag);
	void AbilityInputReleased(FGameplayTag InputTag);

	UAuraAbilitySystemComponent* GetASC();
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Asset|Input")
	TObjectPtr<UInputMappingContext> AuraMappingContext;

	UPROPERTY(EditDefaultsOnly, Category="Asset|Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="Asset|Input")
	TObjectPtr<UInputAction> ShiftAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Asset|Input")
	TObjectPtr<UAuraInputConfig> InputConfig;
	
private:
	TObjectPtr<IHighlightInterface> LastHighlightedActor = nullptr;
	TObjectPtr<IHighlightInterface> CurrHighlightedActor = nullptr;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

private:
	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;
	FHitResult CursorHit;

	bool bShiftKeyDown = false;
	
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> SplineComponent;
};
