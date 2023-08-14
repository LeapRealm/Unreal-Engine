#include "Creature/CreatureBase.h"

ACreatureBase::ACreatureBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACreatureBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACreatureBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
