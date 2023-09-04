#include "VoxelGameMode.h"

#include "Chunk.h"
#include "NoiseRendererBase.h"
#include "Define.h"
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
	UGameplayStatics::GetAllActorsOfClass(this, ANoiseRendererBase::StaticClass(), Actors);
	for (AActor* Actor : Actors)
	{
		if (ANoiseRendererBase* NoiseRenderer = Cast<ANoiseRendererBase>(Actor))
		{
			switch (NoiseRenderer->Type)
			{
			case ENoiseRendererType::Surface:
				SurfaceNoiseSettings = NoiseRenderer->NoiseSettings;
				break;
			case ENoiseRendererType::Stone:
				StoneNoiseSettings = NoiseRenderer->NoiseSettings;
				break;
			case ENoiseRendererType::DiamondTop:
				DiamondTopNoiseSettings = NoiseRenderer->NoiseSettings;
				break;
			case ENoiseRendererType::DiamondBottom:
				DiamondBottomNoiseSettings = NoiseRenderer->NoiseSettings;
				break;
			case ENoiseRendererType::Cave:
				CaveNoiseSettings = NoiseRenderer->NoiseSettings;
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
				Chunk->SetChunkIndex(FIntVector(x, y, z));
				Chunk->BuildChunkData();
				Chunks.Add(Chunk);
			}
		}
	}

	for (int32 i = 0; i < Chunks.Num(); i++)
		Chunks[i]->BuildChunkMesh();
}
