﻿#include "AuraProjectileSpell.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Actor/AuraProjectile.h"
#include "Interface/CombatInterface.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraProjectileSpell)

UAuraProjectileSpell::UAuraProjectileSpell(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	if (GetAvatarActorFromActorInfo()->HasAuthority() == false)
		return;

	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector Location = CombatInterface->GetCombatSocketLocation();
		FRotator Rotation = (ProjectileTargetLocation - Location).Rotation();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		SpawnTransform.SetRotation(Rotation.Quaternion());

		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetAvatarActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

		UAbilitySystemComponent* SourceASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetAvatarActorFromActorInfo());
		FGameplayEffectSpecHandle EffectSpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
		Projectile->DamageEffectSpecHandle = EffectSpecHandle;

		Projectile->FinishSpawning(SpawnTransform);
	}
}
