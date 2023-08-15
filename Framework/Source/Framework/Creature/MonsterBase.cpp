#include "Creature/MonsterBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Manager/ResourceManager.h"
#include "Util/Tag.h"
#include "Util/Util.h"

AMonsterBase::AMonsterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	CreatureTag = Tag::Creature_Skeleton;
	
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetMesh()->SetRelativeScale3D(FVector(0.8f));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
}

void AMonsterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UUtil::GetResourceManager(this)->LoadAsync<USkeletalMesh>(Tag::Asset_SkeletalMesh_Skeleton, [this](USkeletalMesh* SkeletalMesh)
	{
		GetMesh()->SetSkeletalMesh(SkeletalMesh);
		GetMesh()->SetAnimClass(UUtil::GetDataManager(this)->FindObjectClassForTag(Tag::Asset_AnimBP_Skeleton));
	});
}

void AMonsterBase::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
}

void AMonsterBase::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
}
