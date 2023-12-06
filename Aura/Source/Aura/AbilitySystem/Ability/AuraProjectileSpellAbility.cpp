#include "AuraProjectileSpellAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AuraGameplayTags.h"
#include "Actor/AuraProjectile.h"
#include "Interface/CombatInterface.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraProjectileSpellAbility)

UAuraProjectileSpellAbility::UAuraProjectileSpellAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void UAuraProjectileSpellAbility::SpawnProjectile(const FVector& ProjectileTargetLocation)
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

		const UAbilitySystemComponent* SourceASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetAvatarActorFromActorInfo());

		FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
		EffectContextHandle.SetAbility(this);
		EffectContextHandle.AddSourceObject(Projectile);
		TArray<TWeakObjectPtr<AActor>> Actors;
		Actors.Add(Projectile);
		EffectContextHandle.AddActors(Actors);
		FHitResult HitResult;
		HitResult.Location = ProjectileTargetLocation;
		EffectContextHandle.AddHitResult(HitResult);
		
		const FGameplayEffectSpecHandle EffectSpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);

		const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
		// const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());
		const float ScaledDamage = Damage.GetValueAtLevel(10);

		EffectSpecHandle.Data->SetSetByCallerMagnitude(GameplayTags.Damage, ScaledDamage);
		Projectile->DamageEffectSpecHandle = EffectSpecHandle;

		Projectile->FinishSpawning(SpawnTransform);
	}
}
