#include "Creature/CreatureBase.h"

#include "Components/CapsuleComponent.h"
#include "System/SkillComponent.h"
#include "System/StatComponent.h"

ACreatureBase::ACreatureBase()
{
	PrimaryActorTick.bCanEverTick = false;

	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("StatComponent"));
	SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("SkillComponent"));

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetCapsuleComponent()->SetCapsuleRadius(48.f);
}

void ACreatureBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(CreatureTag.IsValid());
	StatComponent->Init(CreatureTag);
}
