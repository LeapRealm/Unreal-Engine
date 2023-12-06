#pragma once

#include "AuraGameplayAbility.h"
#include "AuraProjectileSpellAbility.generated.h"

class UGameplayEffect;
class AAuraProjectile;

UCLASS()
class UAuraProjectileSpellAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
public:
	UAuraProjectileSpellAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& ProjectileTargetLocation);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AAuraProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};
