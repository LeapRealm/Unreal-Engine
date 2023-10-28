#pragma once

#include "AuraPlayerController.generated.h"

class IHighlightInterface;
class UInputAction;
class UInputMappingContext;
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
	void Move(const FInputActionValue& Value);
	
private:
	UPROPERTY(EditAnywhere, Category="Asset|Input")
	TObjectPtr<UInputMappingContext> AuraMappingContext;

	UPROPERTY(EditAnywhere, Category="Asset|Input")
	TObjectPtr<UInputAction> MoveAction;

private:
	TObjectPtr<IHighlightInterface> LastHighlightedActor = nullptr;
	TObjectPtr<IHighlightInterface> CurrHighlightedActor = nullptr;
};
