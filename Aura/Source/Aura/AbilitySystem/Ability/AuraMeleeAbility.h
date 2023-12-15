#pragma once

#include "AuraDamageGameplayAbility.h"
#include "AuraMeleeAbility.generated.h"

UCLASS()
class UAuraMeleeAbility : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()
	
public:
	UAuraMeleeAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
