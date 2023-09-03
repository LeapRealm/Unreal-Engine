#include "VoxelGameMode.h"

#include "Chunk.h"
#include "GraphRenderer.h"
#include "VoxelCharacter.h"
#include "Kismet/GameplayStatics.h"

AVoxelGameMode::AVoxelGameMode()
{
	DefaultPawnClass = AVoxelCharacter::StaticClass();
}

void AVoxelGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this, AGraphRenderer::StaticClass(), Actors);
	for (AActor* Actor : Actors)
	{
		if (AGraphRenderer* GraphRenderer = Cast<AGraphRenderer>(Actor))
		{
			switch (GraphRenderer->Type)
			{
			case EGraphRendererType::Surface:
				SurfaceGraphSettings = GraphRenderer->GraphSettings;
				break;
			case EGraphRendererType::Mixed:
				MixedGraphSettings = GraphRenderer->GraphSettings;
				break;
			case EGraphRendererType::Stone:
				StoneGraphSettings = GraphRenderer->GraphSettings;
				break;
			}
		}
	}

	const FIntVector& ChunkCount = FVoxel::ChunkCount;
	const FIntVector& BlockCount = FVoxel::BlockCount;
	const int32 BlockSize = FVoxel::BlockSize;
	
	Chunks.Reserve(ChunkCount.X * ChunkCount.Y * ChunkCount.Z);
	for (int32 z = 0; z < ChunkCount.Z; z++)
	{
		for (int32 y = 0; y < ChunkCount.Y; y++)
		{
			for (int32 x = 0; x < ChunkCount.X; x++)
			{
				AChunk* Chunk = GetWorld()->SpawnActor<AChunk>(FVector(x * BlockCount.X, y * BlockCount.Y, z * BlockCount.Z) * BlockSize, FRotator::ZeroRotator);
				Chunk->Init(FIntVector(x, y, z));
				Chunks.Add(Chunk);
			}
		}
	}
}
