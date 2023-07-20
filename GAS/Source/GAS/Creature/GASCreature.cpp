#include "Creature/GASCreature.h"

AGASCreature::AGASCreature()
{
	PrimaryActorTick.bCanEverTick = true;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), FName(TEXT("WeaponHandSocket")));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
