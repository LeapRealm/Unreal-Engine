#include "PerlinGrapher.h"

#include "VoxelFunctionLibrary.h"

APerlinGrapher::APerlinGrapher()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(SceneComponent);
}

void APerlinGrapher::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
	{
		int32 Y = -1;

		TArray<FVector> Positions;
		Positions.Reserve(PositionCount);
		
		for (int32 X = 0; X < PositionCount; X++)
		{
			float Z = UVoxelFunctionLibrary::FBMNoise(FVector2D(X + 10, Y), Octaves, Scale, HeightScale, HeightOffset);
			Positions.Add(FVector(X, Y, Z) * 100);
		}

		for (int32 i = 1; i < Positions.Num(); i++)
		{
			FVector Start = Positions[i - 1];
			FVector End = Positions[i];
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.5f, 0, 10);
		}
	}, 0.5f, true);
}
