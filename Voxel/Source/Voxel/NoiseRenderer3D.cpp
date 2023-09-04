#include "NoiseRenderer3D.h"

#include "VoxelFunctionLibrary.h"
#include "Components/InstancedStaticMeshComponent.h"

ANoiseRenderer3D::ANoiseRenderer3D()
{
	PrimaryActorTick.bCanEverTick = false;

#if WITH_EDITOR
	NoiseSettings = { 0.08f, 2.f, 2, 1.f, 0.2 };
	
	InstancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMesh"));
	InstancedStaticMeshComponent->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Cube(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (SM_Cube.Succeeded())
		InstancedStaticMeshComponent->SetStaticMesh(SM_Cube.Object);
#endif
}

void ANoiseRenderer3D::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

#if WITH_EDITOR
	if (PrevNoiseSettings == NoiseSettings)
		return;

	PrevNoiseSettings = NoiseSettings;
	DrawGraph();
#endif
}

void ANoiseRenderer3D::BeginPlay()
{
	Super::BeginPlay();

#if WITH_EDITOR
	DrawGraph();
#endif
}

void ANoiseRenderer3D::DrawGraph()
{
	Super::DrawGraph();
	
#if WITH_EDITOR
	InstancedStaticMeshComponent->ClearInstances();
	
	for (int32 z = 0; z < BlockCount.Z; z++)
	{
		for (int32 y = 0; y < BlockCount.Y; y++)
		{
			for (int32 x = 0; x < BlockCount.X; x++)
			{
				float Noise = UVoxelFunctionLibrary::FBMNoise3D(FVector(x, y, z),
					NoiseSettings.Octaves, NoiseSettings.Scale, NoiseSettings.HeightScale, NoiseSettings.HeightOffset);

				if (Noise >= NoiseSettings.DrawCutOff)
				{
					FTransform Transform;
					Transform.SetLocation(FVector(x, y, z) * FVoxel::BlockSize);
					InstancedStaticMeshComponent->AddInstance(Transform);
				}
			}
		}
	}
#endif
}
