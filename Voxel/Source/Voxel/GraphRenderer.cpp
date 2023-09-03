#include "GraphRenderer.h"

#include "VoxelFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

AGraphRenderer::AGraphRenderer()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(SceneComponent);
}

void AGraphRenderer::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

#if WITH_EDITOR
	if (TimerHandle.IsValid() == false)
		DrawGraph();
#endif
}

void AGraphRenderer::BeginPlay()
{
	Super::BeginPlay();

#if WITH_EDITOR
	if (TimerHandle.IsValid() == false)
		DrawGraph();
#endif
}

void AGraphRenderer::DrawGraph()
{
#if WITH_EDITOR
	GetWorldTimerManager().SetTimer(TimerHandle, [this]()
	{
		int32 Y = -1;
		TArray<FVector> Positions;
		Positions.Reserve(PositionCount);
				
		for (int32 X = 0; X < PositionCount; X++)
		{
			float Z = UVoxelFunctionLibrary::FBMNoise(FVector2D(X + 10, Y), GraphSettings.Octaves, GraphSettings.Scale, GraphSettings.HeightScale, GraphSettings.HeightOffset);
			Positions.Add(FVector(X, Y, Z) * 100);
		}

		for (int32 i = 1; i < Positions.Num(); i++)
		{
			FVector Start = Positions[i - 1];
			FVector End = Positions[i];
			UKismetSystemLibrary::DrawDebugLine(this, Start, End, Color, 0.25f, LineThickness);
		}
	}, 0.25f, true);
#endif
}
