#pragma once

#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

UCLASS()
class UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UAuraGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(EditDefaultsOnly, Category="Asset|Input")
	FGameplayTag InputTag;
};
