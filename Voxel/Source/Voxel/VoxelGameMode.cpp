#include "VoxelGameMode.h"

#include "BlockingBox.h"
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

	InitInvisibleWalls();
	InitNoise();
	InitChunks();
}

void AVoxelGameMode::InitInvisibleWalls()
{
	const FIntVector& ChunkCount = FVoxel::ChunkCount;
	const FIntVector& BlockCount = FVoxel::BlockCount;
	int32 BlockSize = FVoxel::BlockSize;
	FIntVector ChunkSize = FIntVector(BlockCount.X * BlockSize, BlockCount.Y * BlockSize, BlockCount.Z * BlockSize);
	
	FVector MinLocation = FVector(0, 0, 0);
	FVector MaxLocation = FVector(ChunkSize.X * ChunkCount.X, ChunkSize.Y * ChunkCount.Y, ChunkSize.Z * ChunkCount.Z);
	FVector Center = (MinLocation + MaxLocation) / 2.f;
	FVector BoxSize = (MaxLocation - MinLocation) / 2.f;
	BoxSize.Z *= 1.5f;
	
	TArray<FVector> SpawnLocations;
	TArray<FVector> BoxExtents;
	SpawnLocations.Add(FVector(Center.X, -BlockSize, Center.Z));
	BoxExtents.Add(FVector(BoxSize.X, 100, BoxSize.Z));
	SpawnLocations.Add(FVector(Center.X, MaxLocation.Y + BlockSize, Center.Z));
	BoxExtents.Add(FVector(BoxSize.X, 100, BoxSize.Z));
	SpawnLocations.Add(FVector(-BlockSize, Center.Y, Center.Z));
	BoxExtents.Add(FVector(100, BoxSize.Y, BoxSize.Z));
	SpawnLocations.Add(FVector(MaxLocation.X + BlockSize, Center.Y, Center.Z));
	BoxExtents.Add(FVector(100, BoxSize.Y, BoxSize.Z));
	
	for (int i = 0; i < SpawnLocations.Num(); i++)
	{
		ABlockingBox* BlockingBox = GetWorld()->SpawnActor<ABlockingBox>(SpawnLocations[i], FRotator::ZeroRotator);
		BlockingBox->SetBoxExtent(BoxExtents[i]);
	}
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
	const FIntVector& ChunkCount = FVoxel::ChunkCount;
	const FIntVector& BlockCount = FVoxel::BlockCount;
	
	int32 ChunkIndex1D = UVoxelFunctionLibrary::Index3DTo1D(ChunkIndex3D, ChunkCount);
	int32 BlockIndex1D = UVoxelFunctionLibrary::Index3DTo1D(BlockIndex3D, BlockCount);

	TArray<EBlockType>& BlockTypes = ChunkDatas[ChunkIndex1D].BlockTypes;
	if (BlockTypes[BlockIndex1D] == EBlockType::BedRock)
		return;
	
	BlockTypes[BlockIndex1D] = NewBlockType;
	
	TArray<AChunk*> DirtyChunks;
	DirtyChunks.Add(Chunks[ChunkIndex1D]);
	
	TArray<ESide> ChunkSides;
	if (BlockIndex3D.X == 0)
		ChunkSides.Add(ESide::Backward);
	else if (BlockIndex3D.X == BlockCount.X - 1)
		ChunkSides.Add(ESide::Forward);
	
	if (BlockIndex3D.Y == 0)
		ChunkSides.Add(ESide::Left);
	else if (BlockIndex3D.Y == BlockCount.Y - 1)
		ChunkSides.Add(ESide::Right);
			
	if (BlockIndex3D.Z == 0)
		ChunkSides.Add(ESide::Down);
	else if (BlockIndex3D.Z == BlockCount.Z - 1)
		ChunkSides.Add(ESide::Up);
	
	for (ESide ChunkSide : ChunkSides)
	{
		FIntVector SideChunkIndex3D = ChunkIndex3D + FIntVector(
			FVoxel::DX[static_cast<int32>(ChunkSide)],
			FVoxel::DY[static_cast<int32>(ChunkSide)],
			FVoxel::DZ[static_cast<int32>(ChunkSide)]
		);
		
		if (SideChunkIndex3D.X < 0 || SideChunkIndex3D.X >= ChunkCount.X ||
			SideChunkIndex3D.Y < 0 || SideChunkIndex3D.Y >= ChunkCount.Y ||
			SideChunkIndex3D.Z < 0 || SideChunkIndex3D.Z >= ChunkCount.Z)
			continue;
		
		DirtyChunks.Add(Chunks[UVoxelFunctionLibrary::Index3DTo1D(SideChunkIndex3D, ChunkCount)]);
	}
	
	for (AChunk* DirtyChunk : DirtyChunks)
	{
		AsyncTask(ENamedThreads::AnyThread, [DirtyChunk]()
		{
			DirtyChunk->BuildChunkMesh();
		});
	}
}
