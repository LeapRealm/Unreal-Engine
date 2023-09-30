#include "VoxelGameMode.h"

#include "Chunk.h"
#include "Define.h"
#include "FastNoiseWrapper.h"
#include "VoxelCharacter.h"
#include "VoxelFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

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
	
	Chunks.SetNumZeroed(TotalChunkCount);
	ChunkDatas.SetNum(TotalChunkCount);
	
	for (int32 ChunkIndex1D = 0; ChunkIndex1D < ChunkDatas.Num(); ChunkIndex1D++)
	{
		ChunkDatas[ChunkIndex1D].BlockTypes.SetNumUninitialized(TotalBlockCount);
		ChunkDatas[ChunkIndex1D].BlockStates.SetNumUninitialized(TotalBlockCount);
		
		AsyncTask(ENamedThreads::AnyThread, [this, ChunkIndex1D]()
		{
			UVoxelFunctionLibrary::BuildChunkData(SurfaceNoiseWrapper, UVoxelFunctionLibrary::Index1DTo3D(ChunkIndex1D, FVoxel::ChunkCount), ChunkDatas[ChunkIndex1D]);
			BuiltChunkDataCount.fetch_add(1);
		});
	}
	
	GetWorldTimerManager().SetTimer(CullingChunksTimerHandle, this, &AVoxelGameMode::CullingChunks, CullingChunksTimerRate, true);
}

void AVoxelGameMode::CullingChunks()
{
	if (bBuildChunkDataCompleted == false)
	{
		const FIntVector& ChunkCount = FVoxel::ChunkCount;
		int32 TotalChunkCount = ChunkCount.X * ChunkCount.Y * ChunkCount.Z;
		bBuildChunkDataCompleted = (BuiltChunkDataCount.load() == TotalChunkCount);
		if (bBuildChunkDataCompleted == false)
			return;
	}
	
	if (IsValid(VoxelCharacter) == false)
	{
		VoxelCharacter = Cast<AVoxelCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
		if (VoxelCharacter == nullptr)
			return;
	}

	FIntVector NewPlayerChunkIndex = UVoxelFunctionLibrary::WorldPosToChunkIndex(VoxelCharacter->GetActorLocation());
	if (PlayerChunkIndex == NewPlayerChunkIndex)
		return;

	PlayerChunkIndex = NewPlayerChunkIndex;
	
	FIntVector MinCullIndex, MaxCullIndex;
	if (bCullEnable)
	{
		MinCullIndex = FIntVector(FMath::Max(0, PlayerChunkIndex.X - CullIndexDistance),
								  FMath::Max(0, PlayerChunkIndex.Y - CullIndexDistance),
								  FMath::Max(0, PlayerChunkIndex.Z - CullIndexDistance));
		MaxCullIndex = FIntVector(FMath::Min(FVoxel::ChunkCount.X - 1, PlayerChunkIndex.X + CullIndexDistance),
								  FMath::Min(FVoxel::ChunkCount.Y - 1, PlayerChunkIndex.Y + CullIndexDistance),
								  FMath::Min(FVoxel::ChunkCount.Z - 1, PlayerChunkIndex.Z + CullIndexDistance));
	}
	else
	{
		MinCullIndex = FIntVector(0, 0, 0);
		MaxCullIndex = FIntVector(FVoxel::ChunkCount.X - 1, FVoxel::ChunkCount.Y - 1, FVoxel::ChunkCount.Z - 1);
	}
	
	DestroyFarChunks(MinCullIndex, MaxCullIndex);
	SpawnNearChunks(MinCullIndex, MaxCullIndex);

	if (bCullEnable == false)
	{
		GetWorldTimerManager().ClearTimer(CullingChunksTimerHandle);
		CullingChunksTimerHandle.Invalidate();
		return;
	}
}

void AVoxelGameMode::DestroyFarChunks(const FIntVector& MinCullIndex, const FIntVector& MaxCullIndex)
{
	const FIntVector& ChunkCount = FVoxel::ChunkCount;
	
	for (int32 i = 0; i < SpawnedChunks.Num(); i++)
	{
		AChunk* Chunk = SpawnedChunks[i];
		const FIntVector& ChunkIndex = Chunk->ChunkIndex;

		if (ChunkIndex.X < MinCullIndex.X || ChunkIndex.Y < MinCullIndex.Y || ChunkIndex.Z < MinCullIndex.Z ||
			ChunkIndex.X > MaxCullIndex.X || ChunkIndex.Y > MaxCullIndex.Y || ChunkIndex.Z > MaxCullIndex.Z)
		{
			int32 Index1D = UVoxelFunctionLibrary::Index3DTo1D(ChunkIndex, ChunkCount);
			Chunks[Index1D] = nullptr;
			SpawnedChunks.RemoveAtSwap(i--);
			GetWorld()->DestroyActor(Chunk);
		}
	}
}

void AVoxelGameMode::SpawnNearChunks(const FIntVector& MinCullIndex, const FIntVector& MaxCullIndex)
{
	const FIntVector& ChunkCount = FVoxel::ChunkCount;
	const FIntVector& BlockCount = FVoxel::BlockCount;
	const int32 BlockSize = FVoxel::BlockSize;
	
	for (int32 z = MinCullIndex.Z; z <= MaxCullIndex.Z; z++)
	{
		for (int32 y = MinCullIndex.Y; y <= MaxCullIndex.Y; y++)
		{
			for (int32 x = MinCullIndex.X; x <= MaxCullIndex.X; x++)
			{
				int32 Index1D = UVoxelFunctionLibrary::Index3DTo1D(FIntVector(x, y, z), ChunkCount);
				if (Chunks[Index1D])
					continue;
				
				AChunk* Chunk = GetWorld()->SpawnActor<AChunk>(FVector(x * BlockCount.X, y * BlockCount.Y, z * BlockCount.Z) * BlockSize, FRotator::ZeroRotator);
				Chunk->Init(FIntVector(x, y, z));
				Chunks[Index1D] = Chunk;
				SpawnedChunks.Add(Chunk);

				AsyncTask(ENamedThreads::AnyThread, [Chunk]()
				{
					if (IsValid(Chunk))
						Chunk->BuildChunkMesh();
					
					AsyncTask(ENamedThreads::GameThread, [Chunk]()
					{
						if (IsValid(Chunk))
							Chunk->CreateChunkMesh();
					});
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
	if (BlockTypes[BlockIndex1D] == NewBlockType)
		return;

	// TODO: (모든 BlockType에 대해서) 가장자리 부분일 경우, 주변 청크로 같이 업데이트해야 함
	BlockTypes[BlockIndex1D] = NewBlockType;
	
	AChunk* Chunk = Chunks[ChunkIndex1D];
	AsyncTask(ENamedThreads::AnyThread, [Chunk]()
	{
		if (IsValid(Chunk))
			Chunk->BuildChunkMesh();
		
		AsyncTask(ENamedThreads::GameThread, [Chunk]()
		{
			if (IsValid(Chunk))
				Chunk->CreateChunkMesh();
		});
	});
}

void AVoxelGameMode::UpdateBlockState(const FIntVector& ChunkIndex3D, const FIntVector& BlockIndex3D, EBlockState NewBlockState)
{
	// TODO
}
