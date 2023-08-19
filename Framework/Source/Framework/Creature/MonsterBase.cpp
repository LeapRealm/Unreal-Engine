#include "Creature/MonsterBase.h"

#include "AIControllerBase.h"
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
	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AIControllerClass = AAIControllerBase::StaticClass();
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

void AMonsterBase::OnDamage(const FGameplayTag& StatTag, const FStatData& StatData)
{
	Super::OnDamage(StatTag, StatData);

	if (StatTag != Tag::Stat_Health)
		return;

	if (StatData.Value > StatData.MinValue)
	{
		if (AAIControllerBase* AIControllerBase = Cast<AAIControllerBase>(GetController()))
		{
			if (AIControllerBase->Find360Target())
				AIControllerBase->SetState(EMonsterState::Chase);
		}
	}
	else
	{
		UUtil::GetResourceManager(this)->LoadAsync<UAnimMontage>(Tag::Asset_Montage_Skeleton_Dead, [this](UAnimMontage* AnimMontage) 
		{
			float Duration = GetMesh()->GetAnimInstance()->Montage_Play(AnimMontage, 1.f, EMontagePlayReturnType::Duration);
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this](){ Destroy(); }, Duration + 2.f, false);
		});
	
		GetController()->SetIgnoreMoveInput(true);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		if (AAIControllerBase* AIControllerBase = Cast<AAIControllerBase>(GetController()))
			AIControllerBase->SetState(EMonsterState::Dead);
	}
}
