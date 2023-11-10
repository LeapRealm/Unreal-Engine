#pragma once

#include "AuraGameplayAbility.h"
#include "AuraProjectileSpell.generated.h"

class UGameplayEffect;
class AAuraProjectile;

UCLASS()
class UAuraProjectileSpell : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
public:
	UAuraProjectileSpell(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& ProjectileTargetLocation);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AAuraProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};
