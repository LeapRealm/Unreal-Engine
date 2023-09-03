#include "Chunk.h"

#include "Define.h"
#include "ProceduralMeshComponent.h"
#include "VoxelFunctionLibrary.h"
#include "VoxelGameMode.h"

AChunk::AChunk()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProcMesh"));
	SetRootComponent(ProceduralMeshComponent);
	
	static ConstructorHelpers::FObjectFinder<UMaterial> M_Block(TEXT("/Script/Engine.Material'/Game/Materials/M_Block.M_Block'"));
	if (M_Block.Succeeded())
		Material = M_Block.Object;
}

void AChunk::Init(const FIntVector& InChunkIndex)
{
	ChunkIndex = InChunkIndex;
	
	BuildChunkData();
	BuildChunkMesh();
}

void AChunk::BuildChunkData()
{
	const FIntVector& BlockCount = FVoxel::BlockCount;
	ChunkData.SetNumUninitialized(BlockCount.X * BlockCount.Y * BlockCount.Z);
	
	for (int32 Index1D = 0; Index1D < ChunkData.Num(); Index1D++)
	{
		FIntVector Index3D = UVoxelFunctionLibrary::Index1DTo3D(Index1D, BlockCount);
		Index3D += (ChunkIndex * BlockCount);

		const FGraphSettings& SurfaceSettings = AVoxelGameMode::SurfaceGraphSettings;
		int SurfaceHeight = static_cast<int>(UVoxelFunctionLibrary::FBMNoise(FVector2D(Index3D.X + BlockCount.X, Index3D.Y),
			SurfaceSettings.Octaves, SurfaceSettings.Scale, SurfaceSettings.HeightScale, SurfaceSettings.HeightOffset));

		const FGraphSettings& MixedSettings = AVoxelGameMode::MixedGraphSettings;
		int MixedHeight = static_cast<int>(UVoxelFunctionLibrary::FBMNoise(FVector2D(Index3D.X + BlockCount.X, Index3D.Y),
			MixedSettings.Octaves, MixedSettings.Scale, MixedSettings.HeightScale, MixedSettings.HeightOffset));
		
		const FGraphSettings& StoneSettings = AVoxelGameMode::StoneGraphSettings;
		int StoneHeight = static_cast<int>(UVoxelFunctionLibrary::FBMNoise(FVector2D(Index3D.X + BlockCount.X, Index3D.Y),
			StoneSettings.Octaves, StoneSettings.Scale, StoneSettings.HeightScale, StoneSettings.HeightOffset));

		if (Index3D.Z < StoneHeight)
		{
			ChunkData[Index1D] = EBlockType::Stone;
		}
		else if (Index3D.Z < MixedHeight)
		{
			if (FMath::RandRange(0.f, 1.f) <= MixedSettings.Probability)
				ChunkData[Index1D] = EBlockType::Dirt;
			else
				ChunkData[Index1D] = EBlockType::Stone;
		}
		else if (Index3D.Z < SurfaceHeight)
		{
			ChunkData[Index1D] = EBlockType::Dirt;
		}
		else if (Index3D.Z == SurfaceHeight)
		{
			ChunkData[Index1D] = EBlockType::Grass;
		}
		else
		{
			ChunkData[Index1D] = EBlockType::Air;
		}
	}
}

void AChunk::BuildChunkMesh()
{
	ChunkMesh.Empty();
	
	const FIntVector& BlockCount = FVoxel::BlockCount;
	const int32 BlockSize = FVoxel::BlockSize;
	
	for (int32 z = 0; z < BlockCount.Z; z++)
	{
		for (int32 y = 0; y < BlockCount.Y; y++)
		{
			for (int32 x = 0; x < BlockCount.X; x++)
			{
				int32 Index1D = UVoxelFunctionLibrary::Index3DTo1D(FIntVector(x, y, z), BlockCount);
				UVoxelFunctionLibrary::BuildBlockMesh(this, ChunkData[Index1D], FIntVector(x, y, z), FVector(x, y, z) * BlockSize);
			}
		}
	}

	ProceduralMeshComponent->ClearAllMeshSections();
	UVoxelFunctionLibrary::CreateMeshSection(0, ProceduralMeshComponent, ChunkMesh);
	ProceduralMeshComponent->SetMaterial(0, Material);
}
