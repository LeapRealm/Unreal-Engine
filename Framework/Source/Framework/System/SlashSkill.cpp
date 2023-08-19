#include "System/SlashSkill.h"

#include "NiagaraFunctionLibrary.h"
#include "SkillComponent.h"
#include "StatComponent.h"
#include "Creature/CreatureBase.h"
#include "Creature/MonsterBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Manager/ResourceManager.h"
#include "Util/Tag.h"
#include "Util/Util.h"

USlashSkill::USlashSkill()
{
	CoolTime = 1.5f;
}

bool USlashSkill::CanExecute()
{
	if (Super::CanExecute() == false)
		return false;
	
	if (Owner->GetSkillComponent()->GetAttacking())
		return false;

	if (Owner->GetStatComponent()->GetValue(Tag::Stat_Mana) < RequiredMana)
		return false;
	
	return true;
}

bool USlashSkill::TryExecute()
{
	if (Super::TryExecute() == false)
		return false;

	Execute();
	return true;
}

void USlashSkill::Execute()
{
	Owner->GetSkillComponent()->SetAttacking(true);

	Owner->GetStatComponent()->AddValue(Tag::Stat_Mana, -RequiredMana);
	
	Owner->GetMovementComponent()->StopMovementImmediately();
	Owner->GetController()->SetIgnoreMoveInput(true);
	
	UAnimMontage* SlashMontage = UUtil::GetResourceManager(Owner)->LoadSync<UAnimMontage>(MontageTags[MontageTagIdx], false);
	float Duration = Owner->GetMesh()->GetAnimInstance()->Montage_Play(SlashMontage, 1.f, EMontagePlayReturnType::Duration);
	Duration = Duration / 3.f * 2.f;
	MontageTagIdx = (MontageTagIdx + 1) % MontageTags.Num();

	FTimerHandle AnimHandle;
	Owner->GetWorld()->GetTimerManager().SetTimer(AnimHandle, [this]()
	{
		Owner->GetSkillComponent()->SetAttacking(false);
		Owner->GetController()->SetIgnoreMoveInput(false);
	}, Duration, false);

	FTimerHandle EffectHandle;
	Owner->GetWorld()->GetTimerManager().SetTimer(EffectHandle, [this]()
	{
		FVector Location = Owner->GetActorLocation() + Owner->GetActorForwardVector() * 50.f;
		FRotator Rotation = Owner->GetActorRotation() + FRotator(0.f, -90.f, 0.f);
		if (MontageTagIdx == 1)
			Rotation += FRotator(180.f, 0.f, 0.f);
		
		FVector Scale = FVector(0.5f);
		UUtil::GetResourceManager(Owner)->LoadAsync<UNiagaraSystem>(Tag::Asset_Effect_Slash, [this, Location, Rotation, Scale](UNiagaraSystem* NiagaraSystem)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(Owner, NiagaraSystem, Location, Rotation, Scale);
		}, false);
	}, 0.2f, false);
	
	FVector Start = Owner->GetActorLocation() + (Owner->GetActorForwardVector() * 50.f);
	FVector End   = Start + (Owner->GetActorForwardVector() * 50.f);
	float Radius = 50.f;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { UEngineTypes::ConvertToObjectType(ECC_Pawn) };
	TArray<AActor*> IgnoreActors = { Owner };
	FHitResult HitResult;
	
	if (UKismetSystemLibrary::SphereTraceSingleForObjects(Owner, Start, End, Radius, ObjectTypes, false, IgnoreActors, EDrawDebugTrace::None, HitResult, true))
	{
		if (AMonsterBase* MonsterBase = Cast<AMonsterBase>(HitResult.GetActor()))
		{
			float OwnerAttack = Owner->GetStatComponent()->GetValue(Tag::Stat_Attack);
			float TargetDefense = MonsterBase->GetStatComponent()->GetValue(Tag::Stat_Defense);
			float Damage = OwnerAttack - TargetDefense;
			Damage = FMath::Max(Damage, 0.f);
			UGameplayStatics::ApplyDamage(MonsterBase, Damage, Owner->GetController(), Owner, nullptr);
		}
	}
}
