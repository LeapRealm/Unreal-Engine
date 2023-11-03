#pragma once

#include "AuraUserWidget.h"
#include "AuraAttributeWidget.generated.h"

UCLASS()
class UAuraAttributeWidget : public UAuraUserWidget
{
	GENERATED_BODY()
	
public:
	UAuraAttributeWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
