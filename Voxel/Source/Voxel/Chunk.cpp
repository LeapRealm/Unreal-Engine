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
	ProceduralMeshComponent->bUseAsyncCooking = true;
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
	check(VoxelGameMode);

	FScopeLock ScopeLock(&CriticalSection);

	FMesh ChunkMesh;
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
				UVoxelFunctionLibrary::BuildBlockMesh(ChunkIndex, ChunkMesh, ChunkData.BlockTypes[BlockIndex1D], FIntVector(x, y, z), FVector(x, y, z) * BlockSize);
			}
		}
	}
	
	AsyncTask(ENamedThreads::GameThread, [CachedMesh = MoveTemp(ChunkMesh), this]()
	{
		ProceduralMeshComponent->ClearAllMeshSections();
		UVoxelFunctionLibrary::CreateMeshSection(0, ProceduralMeshComponent, CachedMesh);
		ProceduralMeshComponent->SetMaterial(0, Material);
	});
}
