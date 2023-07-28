#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GASHUD.generated.h"

class UAttributeMenuWidgetController;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UGASUserWidget;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class GAS_API AGASHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
	
public:
	UPROPERTY()
	TObjectPtr<UGASUserWidget> OverlayWidgetRef;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGASUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetControllerRef;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetControllerRef;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
