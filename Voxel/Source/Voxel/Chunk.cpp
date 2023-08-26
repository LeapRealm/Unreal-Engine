#include "Chunk.h"

#include "Define.h"
#include "ProceduralMeshComponent.h"
#include "VoxelFunctionLibrary.h"
#include "VoxelGameMode.h"
#include "Kismet/GameplayStatics.h"

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
	
	AVoxelGameMode* VoxelGameMode = Cast<AVoxelGameMode>(UGameplayStatics::GetGameMode(this));
    check(VoxelGameMode);
    BlockCount = VoxelGameMode->BlockCount;
	BlockSize = VoxelGameMode->BlockSize;
	
	BuildChunkData();
	BuildChunkMesh();
}

void AChunk::BuildChunkData()
{
	ChunkData.SetNumUninitialized(BlockCount.X * BlockCount.Y * BlockCount.Z);
	for (int32 Index1D = 0; Index1D < ChunkData.Num(); Index1D++)
	{
		FIntVector Index3D = UVoxelFunctionLibrary::Index1DTo3D(Index1D, BlockCount);
		Index3D += (ChunkIndex * BlockCount);

		float Z = UVoxelFunctionLibrary::FBMNoise(FVector2D(Index3D.X + BlockCount.X, Index3D.Y), Octaves, Scale, HeightScale, HeightOffset);
		if (Z >= Index3D.Z)
			ChunkData[Index1D] = Dirt;
		else
			ChunkData[Index1D] = Air;
	}
}

void AChunk::BuildChunkMesh()
{
	ChunkMesh.Empty();
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
