#pragma once

#include "AuraDamageGameplayAbility.h"
#include "AuraProjectileSpellAbility.generated.h"

class UGameplayEffect;
class AAuraProjectile;

UCLASS()
class UAuraProjectileSpellAbility : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()
	
public:
	UAuraProjectileSpellAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AAuraProjectile> ProjectileClass;
};
