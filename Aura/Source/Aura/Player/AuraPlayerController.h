﻿#pragma once

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
	
public:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuraMappingContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

private:
	IHighlightInterface* LastHighlightedActor;
	IHighlightInterface* CurrHighlightedActor;
};
