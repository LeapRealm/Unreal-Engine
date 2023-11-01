#include "AuraCharacterBase.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraCharacterBase)

AAuraCharacterBase::AAuraCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	WeaponMeshComponent->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	WeaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}
