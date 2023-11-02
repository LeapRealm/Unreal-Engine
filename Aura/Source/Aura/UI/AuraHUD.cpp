#include "AuraHUD.h"

#include "AuraSceneWidget.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraHUD)

AAuraHUD::AAuraHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void AAuraHUD::Init()
{
	check(SceneWidgetClass);
	SceneWidget = CreateWidget<UAuraSceneWidget>(GetWorld(), SceneWidgetClass);
	SceneWidget->AddToViewport();
}
