#include "Creature/CreatureBase.h"

#include "System/SkillComponent.h"
#include "System/StatComponent.h"

ACreatureBase::ACreatureBase()
{
	PrimaryActorTick.bCanEverTick = false;

	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("StatComponent"));
	SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("SkillComponent"));
}

void ACreatureBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(CreatureTag.IsValid());
	StatComponent->Init(CreatureTag);
}
