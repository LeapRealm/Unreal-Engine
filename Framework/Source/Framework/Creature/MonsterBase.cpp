#include "Creature/MonsterBase.h"

#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Manager/ResourceManager.h"
#include "System/StatComponent.h"
#include "Util/Tag.h"
#include "Util/Util.h"
#include "Widget/Widget_Nameplate.h"

AMonsterBase::AMonsterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	CreatureTag = Tag::Creature_Skeleton;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetRootComponent());
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawAtDesiredSize(true);
	WidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetMesh()->SetRelativeScale3D(FVector(0.8f));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AMonsterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UUtil::GetResourceManager(this)->LoadAsync<USkeletalMesh>(Tag::Asset_SkeletalMesh_Skeleton, [this](USkeletalMesh* SkeletalMesh)
	{
		GetMesh()->SetSkeletalMesh(SkeletalMesh);
		GetMesh()->SetAnimClass(UUtil::GetDataManager(this)->FindObjectClassForTag(Tag::Asset_AnimBP_Skeleton));
	});

	WidgetComponent->SetWidgetClass(UUtil::GetDataManager(this)->FindWidgetClassForTag(Tag::Asset_Widget_Nameplate));
}

void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();

	GetStatComponent()->AddDelegate(Tag::Stat_Health, Cast<UWidget_Nameplate>(WidgetComponent->GetWidget()), &UWidget_Nameplate::RefreshUI);
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
