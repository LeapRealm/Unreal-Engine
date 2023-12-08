#pragma once

#include "Components/WidgetComponent.h"
#include "DamageTextComponent.generated.h"

UCLASS()
class UDamageTextComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UDamageTextComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDamageText(float Damage, bool bIsBlockedHit, bool bIsCriticalHit);
};
