#pragma once

#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraSceneWidget;

UCLASS()
class AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AAuraHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void ShowSceneWidget();

public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAuraSceneWidget> SceneWidget;
	
	UPROPERTY(EditDefaultsOnly, Category="Asset|Class")
	TSubclassOf<UAuraSceneWidget> SceneWidgetClass;
};
