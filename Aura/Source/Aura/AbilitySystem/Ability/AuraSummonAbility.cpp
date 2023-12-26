#include "AuraSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraSummonAbility)

UAuraSummonAbility::UAuraSummonAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / NumMinions;

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2.f, FVector::UpVector);
	TArray<FVector> SpawnLocations;
	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, ChosenSpawnLocation + FVector(0.f, 0.f, 480.f), ChosenSpawnLocation - FVector(0.f, 0.f, 400.f), ECC_Visibility);
		if (HitResult.bBlockingHit)
		{
			ChosenSpawnLocation = HitResult.ImpactPoint;
		}
		SpawnLocations.Emplace(ChosenSpawnLocation);
	}
	return SpawnLocations;
}
