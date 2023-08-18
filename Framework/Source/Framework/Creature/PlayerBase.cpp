#include "Creature/PlayerBase.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Manager/ResourceManager.h"
#include "System/ManaRegenSkill.h"
#include "System/SkillComponent.h"
#include "System/SlashSkill.h"
#include "Util/Tag.h"
#include "Util/Util.h"

APlayerBase::APlayerBase()
{
	PrimaryActorTick.bCanEverTick = false;

	CreatureTag = Tag::Creature_Player;
	
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->TargetArmLength = 750.f;
	SpringArmComponent->SetRelativeRotation((FRotator(-45.f, 0.f, 0.f)));
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bInheritYaw = false;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 800.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
}

void APlayerBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UUtil::GetResourceManager(this)->LoadAsync<USkeletalMesh>(Tag::Asset_SkeletalMesh_Player, [this](USkeletalMesh* SkeletalMesh)
	{
		GetMesh()->SetSkeletalMesh(SkeletalMesh);
		GetMesh()->SetAnimInstanceClass(UUtil::GetDataManager(this)->FindObjectClassForTag(Tag::Asset_AnimBP_Player));
	});
	
	GetSkillComponent()->AddSkill<USlashSkill>(Tag::Skill_Slash);
	GetSkillComponent()->AddSkill<UManaRegenSkill>(Tag::Skill_ManaRegen);
	GetSkillComponent()->TryInfinite(Tag::Skill_ManaRegen);
}
