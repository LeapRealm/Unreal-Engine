#include "System/SlashSkill.h"

#include "SkillComponent.h"
#include "Creature/CreatureBase.h"
#include "Creature/MonsterBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Manager/ResourceManager.h"
#include "Util/Tag.h"
#include "Util/Util.h"

USlashSkill::USlashSkill()
{
	CoolTime = 2.f;
}

bool USlashSkill::CanExecute()
{
	if (Super::CanExecute() == false)
		return false;
	
	if (Owner->GetSkillComponent()->GetAttacking())
		return false;
	
	return true;
}

bool USlashSkill::TryExecute()
{
	if (Super::TryExecute() == false)
		return false;

	Owner->GetSkillComponent()->SetAttacking(true);
	
	Owner->GetMovementComponent()->StopMovementImmediately();
	Owner->GetController()->SetIgnoreMoveInput(true);
	
	UAnimMontage* SlashMontage = UUtil::GetResourceManager(Owner)->LoadSync<UAnimMontage>(Tag::Asset_Montage_PlayerSlash, false);
	float MontageTime = Owner->GetMesh()->GetAnimInstance()->Montage_Play(SlashMontage);

	FTimerHandle Handle;
	Owner->GetWorld()->GetTimerManager().SetTimer(Handle, [this]()
	{
		Owner->GetSkillComponent()->SetAttacking(false);
		Owner->GetController()->SetIgnoreMoveInput(false);
	}, MontageTime, false);
	
	// TODO: 이펙트
	
	FVector Start = Owner->GetActorLocation() + (Owner->GetActorForwardVector() * 50.f);
	FVector End   = Start + (Owner->GetActorForwardVector() * 50.f);
	float Radius = 50.f;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { UEngineTypes::ConvertToObjectType(ECC_Pawn) };
	TArray<AActor*> IgnoreActors = { Owner };
	FHitResult HitResult;
	bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(Owner, Start, End, Radius, ObjectTypes, false, IgnoreActors, EDrawDebugTrace::ForDuration, HitResult, true);
	if (bHit)
	{
		if (AMonsterBase* MonsterBase = Cast<AMonsterBase>(HitResult.GetActor()))
		{
			// TODO: ApplyDamage
		}
	}
		
	return true;
}
