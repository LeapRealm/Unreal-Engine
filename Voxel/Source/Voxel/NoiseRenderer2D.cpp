#include "NoiseRenderer2D.h"

#include "VoxelFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

ANoiseRenderer2D::ANoiseRenderer2D()
{
	PrimaryActorTick.bCanEverTick = true;

#if WITH_EDITOR
	NoiseSettings = { 0.001f, 5.887208f, 8, 20.f };
#endif
}

void ANoiseRenderer2D::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
#if WITH_EDITOR
	PassedTime += DeltaSeconds;
	if (PassedTime >= TickTime)
	{
		PassedTime = 0.f;
		DrawGraph();
	}
#endif
}

void ANoiseRenderer2D::DrawGraph()
{
	Super::DrawGraph();
	
#if WITH_EDITOR
	int32 Y = -1;
	TArray<FVector> Positions;
	Positions.Reserve(PositionCount);
				
	for (int32 X = 0; X < PositionCount; X++)
	{
		float Z = UVoxelFunctionLibrary::FBMNoise2D(FVector2D(X, Y),
			NoiseSettings.Octaves, NoiseSettings.Scale, NoiseSettings.HeightScale, NoiseSettings.HeightOffset);
		Positions.Add(FVector(X, Y, Z) * 100);
	}

	for (int32 i = 1; i < Positions.Num(); i++)
	{
		FVector Start = Positions[i - 1];
		FVector End = Positions[i];
		UKismetSystemLibrary::DrawDebugLine(this, Start, End, Color, TickTime + 0.05f, LineThickness);
	}
#endif
}
