#include "VoxelGameMode.h"

#include "Chunk.h"
#include "Define.h"
#include "FastNoiseWrapper.h"
#include "VoxelCharacter.h"

AVoxelGameMode::AVoxelGameMode()
{
	DefaultPawnClass = AVoxelCharacter::StaticClass();
	
	SurfaceNoiseWrapper = CreateDefaultSubobject<UFastNoiseWrapper>(TEXT("FastNoiseWrapper"));
}

void AVoxelGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitNoise();
	BuildChunks();
}

void AVoxelGameMode::InitNoise()
{
	SurfaceNoiseWrapper->SetupFastNoise(SurfaceNoiseSettings.NoiseType, Seed,
		SurfaceNoiseSettings.Frequency, EFastNoise_Interp::Quintic, EFastNoise_FractalType::FBM,
		SurfaceNoiseSettings.Octaves, SurfaceNoiseSettings.Lacunarity, SurfaceNoiseSettings.Gain);
}

void AVoxelGameMode::BuildChunks()
{
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
				Chunks.Add(Chunk);
			}
		}
	}

	AsyncTask(ENamedThreads::AnyThread, [this]()
	{
		for (int32 i = 0; i < Chunks.Num(); i++)
		{
			AChunk* Chunk = Chunks[i];
			if (IsValid(Chunk))
				Chunks[i]->BuildChunkData();
		}

		for (int32 i = 0; i < Chunks.Num(); i++)
		{
			AChunk* Chunk = Chunks[i];
			if (IsValid(Chunk))
			{
				Chunks[i]->BuildChunkMesh();
				AsyncTask(ENamedThreads::GameThread, [Chunk]()
				{
					if (IsValid(Chunk))
						Chunk->CreateChunkMesh();
				});
			}
		}
	});
}
