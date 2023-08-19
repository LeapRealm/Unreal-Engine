#include "Creature/AIControllerBase.h"

#include "MonsterBase.h"
#include "PlayerBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Manager/ResourceManager.h"
#include "System/StatComponent.h"
#include "Util/Tag.h"
#include "Util/Util.h"

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAIControllerBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetPawn() == nullptr)
		return;
	
	switch (State)
	{
	case EMonsterState::Search:	TickSearch(DeltaSeconds);	break;
	case EMonsterState::Chase:	TickChase(DeltaSeconds);	break;
	case EMonsterState::Attack:	TickAttack(DeltaSeconds);	break;
	case EMonsterState::Dead:	TickDead(DeltaSeconds);		break;
	}
}

void AAIControllerBase::TickSearch(float DeltaSeconds)
{
	CurrSearchDuration += DeltaSeconds;
	if (CurrSearchDuration >= TargetSearchDuration)
	{
		CurrSearchDuration = 0.f;

		if (Find180Target())
		{
			SetState(EMonsterState::Chase);
			return;
		}
	}
}

void AAIControllerBase::TickChase(float DeltaSeconds)
{
	if (TargetPlayer == nullptr)
	{
		SetState(EMonsterState::Search);
		return;
	}

	if (TargetPlayer->GetStatComponent()->GetValue(Tag::Stat_Health) <= TargetPlayer->GetStatComponent()->GetMinValue(Tag::Stat_Health))
	{
		TargetPlayer = nullptr;
		SetState(EMonsterState::Search);
		return;
	}

	FVector SelfToTarget = TargetPlayer->GetActorLocation() - GetPawn()->GetActorLocation();
	float SelfToTargetLength = SelfToTarget.Length();
	if (SelfToTargetLength > SearchDistance)
	{
		SetState(EMonsterState::Search);
		return;
	}
	else if (SelfToTargetLength <= AttackDistance)
	{
		SetState(EMonsterState::Attack);
		return;
	}
	
	const FVector WorldDirection = SelfToTarget.GetSafeNormal();
	GetPawn()->AddMovementInput(WorldDirection);
}

void AAIControllerBase::TickAttack(float DeltaSeconds)
{
	if (TargetPlayer == nullptr)
	{
		SetState(EMonsterState::Search);
		return;
	}
	
	if (TargetPlayer->GetStatComponent()->GetValue(Tag::Stat_Health) <= TargetPlayer->GetStatComponent()->GetMinValue(Tag::Stat_Health))
	{
		TargetPlayer = nullptr;
		SetState(EMonsterState::Search);
		return;
	}
	
	FVector SelfToTarget = TargetPlayer->GetActorLocation() - GetPawn()->GetActorLocation();
	float SelfToTargetLength = SelfToTarget.Length();
	if (SelfToTargetLength > AttackDistance)
	{
		SetState(EMonsterState::Chase);
		return;
	}

	CurrAttackDuration += DeltaSeconds;
	if (CurrAttackDuration >= TargetAttackDuration)
	{
		CurrAttackDuration = 0.f;
		
		FRotator Rotation = GetPawn()->GetActorRotation();
		Rotation.Yaw = UKismetMathLibrary::FindLookAtRotation(GetPawn()->GetActorLocation(), TargetPlayer->GetActorLocation()).Yaw;
		GetPawn()->SetActorRotation(Rotation);
		Attack();
		return;
	}
}

void AAIControllerBase::TickDead(float DeltaSeconds)
{
	
}

bool AAIControllerBase::Find360Target()
{
	FVector Start = GetPawn()->GetActorLocation();
	FVector End   = Start;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { UEngineTypes::ConvertToObjectType(ECC_Pawn) };
	TArray<AActor*> IgnoreActors = { GetPawn() };
	TArray<FHitResult> HitResults;

	TargetPlayer = nullptr;
	if (UKismetSystemLibrary::SphereTraceMultiForObjects(this, Start, End, SearchDistance, ObjectTypes, false, IgnoreActors, EDrawDebugTrace::None, HitResults, true))
	{
		for (const FHitResult& HitResult : HitResults)
		{
			if (APlayerBase* PlayerBase = Cast<APlayerBase>(HitResult.GetActor()))
			{
				TargetPlayer = PlayerBase;
				break;
			}
		}
	}
	return TargetPlayer ? true : false;
}

bool AAIControllerBase::Find180Target()
{
	FVector Start = GetPawn()->GetActorLocation();
	FVector End   = Start;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { UEngineTypes::ConvertToObjectType(ECC_Pawn) };
	TArray<AActor*> IgnoreActors = { GetPawn() };
	TArray<FHitResult> HitResults;
	
	TargetPlayer = nullptr;
	if (UKismetSystemLibrary::SphereTraceMultiForObjects(this, Start, End, SearchDistance, ObjectTypes, false, IgnoreActors, EDrawDebugTrace::None, HitResults, true))
	{
		for (const FHitResult& HitResult : HitResults)
		{
			if (APlayerBase* PlayerBase = Cast<APlayerBase>(HitResult.GetActor()))
			{
				FVector SelfToTarget = PlayerBase->GetActorLocation() - GetPawn()->GetActorLocation();
				if (SelfToTarget.GetSafeNormal().Dot(GetPawn()->GetActorForwardVector()) > 0)
				{
					TargetPlayer = PlayerBase;
					break;
				}
			}
		}
	}
	return TargetPlayer ? true : false;
}

void AAIControllerBase::Attack()
{
	AMonsterBase* MonsterBase = Cast<AMonsterBase>(GetPawn());
	if (MonsterBase == nullptr)
		return;
	
	MonsterBase->GetMovementComponent()->StopMovementImmediately();
	MonsterBase->GetController()->SetIgnoreMoveInput(true);
	
	UAnimMontage* AttackMontage = UUtil::GetResourceManager(MonsterBase)->LoadSync<UAnimMontage>(Tag::Asset_Montage_Skeleton_Attack, false);
	float Duration = MonsterBase->GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage, 1.f, EMontagePlayReturnType::Duration);

	FTimerHandle AnimHandle;
	MonsterBase->GetWorld()->GetTimerManager().SetTimer(AnimHandle, [MonsterBase]()
	{
		MonsterBase->GetController()->SetIgnoreMoveInput(false);
	}, Duration, false);
	
	FVector Start = MonsterBase->GetActorLocation() + (MonsterBase->GetActorForwardVector() * 50.f);
	FVector End   = Start + (MonsterBase->GetActorForwardVector() * 50.f);
	float Radius = 50.f;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { UEngineTypes::ConvertToObjectType(ECC_Pawn) };
	TArray<AActor*> IgnoreActors = { MonsterBase };
	FHitResult HitResult;
	
	if (UKismetSystemLibrary::SphereTraceSingleForObjects(MonsterBase, Start, End, Radius, ObjectTypes, false, IgnoreActors, EDrawDebugTrace::None, HitResult, true))
	{
		if (APlayerBase* PlayerBase = Cast<APlayerBase>(HitResult.GetActor()))
		{
			float OwnerAttack = MonsterBase->GetStatComponent()->GetValue(Tag::Stat_Attack);
			float TargetDefense = PlayerBase->GetStatComponent()->GetValue(Tag::Stat_Defense);
			float Damage = OwnerAttack - TargetDefense;
			Damage = FMath::Max(Damage, 0.f);
			UGameplayStatics::ApplyDamage(PlayerBase, Damage, MonsterBase->GetController(), MonsterBase, nullptr);
		}
	}
}

void AAIControllerBase::SetState(EMonsterState NewState)
{
	State = NewState;
	
	switch (State)
	{
	case EMonsterState::Search:	CurrSearchDuration = 0.f;					break;
	case EMonsterState::Attack:	CurrAttackDuration = TargetAttackDuration;	break;
	}
}
