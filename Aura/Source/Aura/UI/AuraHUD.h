#pragma once

#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraSceneWidget;
class UAuraUserWidget;

UCLASS()
class AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AAuraHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void Init();

public:
	UPROPERTY()
	TObjectPtr<UAuraSceneWidget> SceneWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraSceneWidget> SceneWidgetClass;
};
