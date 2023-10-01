#include "Chunk.h"

#include "Define.h"
#include "ProceduralMeshComponent.h"
#include "VoxelFunctionLibrary.h"
#include "VoxelGameMode.h"
#include "Kismet/GameplayStatics.h"

AChunk::AChunk()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMeshComponent"));
	ProceduralMeshComponent->bUseAsyncCooking = false;
	SetRootComponent(ProceduralMeshComponent);
	
	static ConstructorHelpers::FObjectFinder<UMaterial> M_Block(TEXT("/Script/Engine.Material'/Game/Materials/M_Block.M_Block'"));
	if (M_Block.Succeeded())
		Material = M_Block.Object;
}

void AChunk::Init(const FIntVector& NewChunkIndex)
{
	ChunkIndex = NewChunkIndex;
}

void AChunk::BuildChunkMesh()
{
	AVoxelGameMode* VoxelGameMode = Cast<AVoxelGameMode>(UGameplayStatics::GetGameMode(this));
	if (VoxelGameMode == nullptr)
		return;

	FScopeLock ScopeLock(&CriticalSection);
	
	ChunkMesh.Empty();
	
	const int32 BlockSize = FVoxel::BlockSize;
	const FIntVector& BlockCount = FVoxel::BlockCount;
	const FIntVector& ChunkCount = FVoxel::ChunkCount;

	int32 ChunkIndex1D = UVoxelFunctionLibrary::Index3DTo1D(ChunkIndex, ChunkCount);
	const FChunkData& ChunkData = VoxelGameMode->ChunkDatas[ChunkIndex1D];
	
	for (int32 z = 0; z < BlockCount.Z; z++)
	{
		for (int32 y = 0; y < BlockCount.Y; y++)
		{
			for (int32 x = 0; x < BlockCount.X; x++)
			{
				int32 BlockIndex1D = UVoxelFunctionLibrary::Index3DTo1D(FIntVector(x, y, z), BlockCount);
				UVoxelFunctionLibrary::BuildBlockMesh(this, ChunkData.BlockTypes[BlockIndex1D], FIntVector(x, y, z), FVector(x, y, z) * BlockSize);
			}
		}
	}
}

void AChunk::CreateChunkMesh()
{
	FScopeLock ScopeLock(&CriticalSection);
	
	ProceduralMeshComponent->ClearAllMeshSections();
	UVoxelFunctionLibrary::CreateMeshSection(0, ProceduralMeshComponent, ChunkMesh);
	ProceduralMeshComponent->SetMaterial(0, Material);
}
