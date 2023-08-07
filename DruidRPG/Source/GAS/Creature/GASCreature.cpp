#include "Creature/GASCreature.h"

#include "AbilitySystemComponent.h"
#include "GAS.h"
#include "GASAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"

AGASCreature::AGASCreature()
{
	PrimaryActorTick.bCanEverTick = true;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), FName(TEXT("WeaponHandSocket")));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
}

void AGASCreature::BeginPlay()
{
	Super::BeginPlay();
}

void AGASCreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGASCreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGASCreature::InitializeDefaultAttributes()
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void AGASCreature::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GamePlayEffectClass, float Level)
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GamePlayEffectClass);

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GamePlayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AGASCreature::AddCharacterAbilities()
{
	UGASAbilitySystemComponent* ASC = CastChecked<UGASAbilitySystemComponent>(AbilitySystemComponent);
	if (HasAuthority() == false)
		return;
	
	ASC->AddCharacterAbilities(StartupAbilities);
}

FVector AGASCreature::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}
