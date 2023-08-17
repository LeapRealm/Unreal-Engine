#include "Creature/CreatureBase.h"

#include "Components/CapsuleComponent.h"
#include "System/SkillComponent.h"
#include "System/StatComponent.h"
#include "Util/Tag.h"

ACreatureBase::ACreatureBase()
{
	PrimaryActorTick.bCanEverTick = false;

	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("StatComponent"));
	SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("SkillComponent"));
	
	GetCapsuleComponent()->SetCapsuleRadius(65.f);
}

void ACreatureBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(CreatureTag.IsValid());
	StatComponent->Init(CreatureTag);
}

float ACreatureBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (GetStatComponent()->GetValue(Tag::Stat_Health) == GetStatComponent()->GetMinValue(Tag::Stat_Health))
		return DamageAmount;
	
	GetStatComponent()->AddValue(Tag::Stat_Health, -DamageAmount);
	return DamageAmount;
}
