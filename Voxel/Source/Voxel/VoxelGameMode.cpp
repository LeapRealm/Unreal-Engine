#include "VoxelGameMode.h"

#include "Chunk.h"
#include "Define.h"
#include "FastNoiseWrapper.h"
#include "VoxelCharacter.h"
#include "VoxelFunctionLibrary.h"

AVoxelGameMode::AVoxelGameMode()
{
	DefaultPawnClass = AVoxelCharacter::StaticClass();
	SurfaceNoiseWrapper = CreateDefaultSubobject<UFastNoiseWrapper>(TEXT("SurfaceNoiseWrapper"));
}

void AVoxelGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitNoise();
	InitChunks();
}

void AVoxelGameMode::InitNoise()
{
	const FFastNoiseSettings& SurfaceNoiseSettings = FVoxel::SurfaceNoiseSettings;
	SurfaceNoiseWrapper->SetupFastNoise(SurfaceNoiseSettings.NoiseType, Seed,
		SurfaceNoiseSettings.Frequency, EFastNoise_Interp::Quintic, EFastNoise_FractalType::FBM,
		SurfaceNoiseSettings.Octaves, SurfaceNoiseSettings.Lacunarity, SurfaceNoiseSettings.Gain);
}

void AVoxelGameMode::InitChunks()
{
	const FIntVector& ChunkCount = FVoxel::ChunkCount;
	const int32 TotalChunkCount = ChunkCount.X * ChunkCount.Y * ChunkCount.Z;

	const FIntVector& BlockCount = FVoxel::BlockCount;
	const int32 TotalBlockCount = BlockCount.X * BlockCount.Y * BlockCount.Z;
	
	ChunkDatas.SetNum(TotalChunkCount);
	
	for (int32 ChunkIndex1D = 0; ChunkIndex1D < ChunkDatas.Num(); ChunkIndex1D++)
	{
		ChunkDatas[ChunkIndex1D].BlockTypes.SetNumUninitialized(TotalBlockCount);
		ChunkDatas[ChunkIndex1D].BlockStates.SetNumUninitialized(TotalBlockCount);
		
		AsyncTask(ENamedThreads::AnyThread, [this, ChunkIndex1D, TotalChunkCount]()
		{
			UVoxelFunctionLibrary::BuildChunkData(SurfaceNoiseWrapper, UVoxelFunctionLibrary::Index1DTo3D(ChunkIndex1D, FVoxel::ChunkCount), ChunkDatas[ChunkIndex1D]);
			if (BuiltChunkDataCount.fetch_add(1) == (TotalChunkCount - 1))
				AsyncTask(ENamedThreads::GameThread, [this](){ SpawnChunks(); });
		});
	}
}

void AVoxelGameMode::SpawnChunks()
{
	const FIntVector& ChunkCount = FVoxel::ChunkCount;
	const int32 TotalChunkCount = ChunkCount.X * ChunkCount.Y * ChunkCount.Z;

	const FIntVector& BlockCount = FVoxel::BlockCount;
	const int32 BlockSize = FVoxel::BlockSize;

	const FIntVector MinChunkIndex = FIntVector(0, 0, 0);
	const FIntVector MaxChunkIndex = FIntVector(ChunkCount.X - 1, ChunkCount.Y - 1, ChunkCount.Z - 1);
	
	Chunks.SetNumZeroed(TotalChunkCount);
	
	for (int32 z = MinChunkIndex.Z; z <= MaxChunkIndex.Z; z++)
	{
		for (int32 y = MinChunkIndex.Y; y <= MaxChunkIndex.Y; y++)
		{
			for (int32 x = MinChunkIndex.X; x <= MaxChunkIndex.X; x++)
			{
				int32 Index1D = UVoxelFunctionLibrary::Index3DTo1D(FIntVector(x, y, z), ChunkCount);
				if (Chunks[Index1D])
					continue;
				
				AChunk* Chunk = GetWorld()->SpawnActor<AChunk>(FVector(x * BlockCount.X, y * BlockCount.Y, z * BlockCount.Z) * BlockSize, FRotator::ZeroRotator);
				Chunk->Init(FIntVector(x, y, z));
				Chunks[Index1D] = Chunk;

				AsyncTask(ENamedThreads::AnyThread, [Chunk]()
				{
					Chunk->BuildChunkMesh();
				});
			}
		}
	}
}

void AVoxelGameMode::UpdateBlockType(const FIntVector& ChunkIndex3D, const FIntVector& BlockIndex3D, EBlockType NewBlockType)
{
	int32 ChunkIndex1D = UVoxelFunctionLibrary::Index3DTo1D(ChunkIndex3D, FVoxel::ChunkCount);
	int32 BlockIndex1D = UVoxelFunctionLibrary::Index3DTo1D(BlockIndex3D, FVoxel::BlockCount);

	TArray<EBlockType>& BlockTypes = ChunkDatas[ChunkIndex1D].BlockTypes;
	BlockTypes[BlockIndex1D] = NewBlockType;

	// TODO: (모든 BlockType에 대해서) 가장자리 부분일 경우, 주변 청크로 같이 업데이트해야 함

	TArray<AChunk*> DirtyChunks;
	DirtyChunks.Add(Chunks[ChunkIndex1D]);
	
	for (AChunk* DirtyChunk : DirtyChunks)
	{
		AsyncTask(ENamedThreads::AnyThread, [DirtyChunk]()
		{
			DirtyChunk->BuildChunkMesh();
		});
	}
}

void AVoxelGameMode::UpdateBlockState(const FIntVector& ChunkIndex3D, const FIntVector& BlockIndex3D, EBlockState NewBlockState)
{
	// TODO
}
