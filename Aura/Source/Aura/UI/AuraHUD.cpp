#include "AuraHUD.h"

#include "AuraSceneWidget.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraHUD)

AAuraHUD::AAuraHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void AAuraHUD::ShowSceneWidget()
{
	check(SceneWidgetClass);

	if (IsValid(SceneWidget) == false)
	{
		SceneWidget = CreateWidget<UAuraSceneWidget>(GetWorld(), SceneWidgetClass);
		SceneWidget->AddToViewport();
	}
}
