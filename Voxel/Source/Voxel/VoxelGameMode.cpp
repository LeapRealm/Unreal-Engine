#include "VoxelGameMode.h"

#include "Chunk.h"

void AVoxelGameMode::BeginPlay()
{
	Super::BeginPlay();

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
