#include "Chunk.h"

#include "Define.h"
#include "ProceduralMeshComponent.h"
#include "VoxelFunctionLibrary.h"
#include "VoxelGameMode.h"

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
	
	BuildChunkData();
	BuildChunkMesh();
}

void AChunk::BuildChunkData()
{
	const FIntVector& BlockCount = FVoxel::BlockCount;
	BlockTypes.SetNumUninitialized(BlockCount.X * BlockCount.Y * BlockCount.Z);
	BlockStates.SetNumUninitialized(BlockCount.X * BlockCount.Y * BlockCount.Z);
	
	for (int32 Index1D = 0; Index1D < BlockTypes.Num(); Index1D++)
	{
		FIntVector Index3D = UVoxelFunctionLibrary::Index1DTo3D(Index1D, BlockCount);
		Index3D += (ChunkIndex * BlockCount);

		const FGraphSettings& SurfaceSettings = AVoxelGameMode::SurfaceGraphSettings;
		int32 SurfaceHeight = static_cast<int32>(UVoxelFunctionLibrary::FBMNoise2D(FVector2D(Index3D.X + BlockCount.X, Index3D.Y),
			SurfaceSettings.Octaves, SurfaceSettings.Scale, SurfaceSettings.HeightScale, SurfaceSettings.HeightOffset));
		
		const FGraphSettings& StoneSettings = AVoxelGameMode::StoneGraphSettings;
		int32 StoneHeight = static_cast<int32>(UVoxelFunctionLibrary::FBMNoise2D(FVector2D(Index3D.X + BlockCount.X, Index3D.Y),
			StoneSettings.Octaves, StoneSettings.Scale, StoneSettings.HeightScale, StoneSettings.HeightOffset));

		const FGraphSettings& DiamondTopSettings = AVoxelGameMode::DiamondTopGraphSettings;
		int32 DiamondTopHeight = static_cast<int32>(UVoxelFunctionLibrary::FBMNoise2D(FVector2D(Index3D.X + BlockCount.X, Index3D.Y),
			DiamondTopSettings.Octaves, DiamondTopSettings.Scale, DiamondTopSettings.HeightScale, DiamondTopSettings.HeightOffset));

		const FGraphSettings& DiamondBottomSettings = AVoxelGameMode::DiamondBottomGraphSettings;
		int32 DiamondBottomHeight = static_cast<int32>(UVoxelFunctionLibrary::FBMNoise2D(FVector2D(Index3D.X + BlockCount.X, Index3D.Y),
			DiamondBottomSettings.Octaves, DiamondBottomSettings.Scale, DiamondBottomSettings.HeightScale, DiamondBottomSettings.HeightOffset));

		if (Index3D.Z < DiamondBottomHeight)
		{
			BlockTypes[Index1D] = EBlockType::Stone;
		}
		else if (Index3D.Z < DiamondTopHeight)
		{
			float Percent = 0.f;
			float RandValue = FMath::RandRange(0.f, 100.f);
			
			if (RandValue <= (Percent += FVoxel::IronPercent))
				BlockTypes[Index1D] = EBlockType::Iron;
			else if (RandValue <= (Percent += FVoxel::DiamondPercent))
				BlockTypes[Index1D] = EBlockType::Diamond;
			else
				BlockTypes[Index1D] = EBlockType::Stone;
		}
		else if (Index3D.Z < StoneHeight)
		{
			float Percent = 0.f;
			float RandValue = FMath::RandRange(0.f, 100.f);
			
			if (RandValue <= (Percent += FVoxel::CoalPercent))
				BlockTypes[Index1D] = EBlockType::Coal;
			else if (RandValue <= (Percent += FVoxel::IronPercent))
				BlockTypes[Index1D] = EBlockType::Iron;
			else if (RandValue <= (Percent += FVoxel::GoldPercent))
				BlockTypes[Index1D] = EBlockType::Gold;
			else
				BlockTypes[Index1D] = EBlockType::Stone;
		}
		else if (Index3D.Z < (StoneHeight + SurfaceHeight) / 2)
		{
			float RandValue = FMath::RandRange(0.f, 100.f);
			
			if (RandValue <= 50.f)
				BlockTypes[Index1D] = EBlockType::Dirt;
			else
				BlockTypes[Index1D] = EBlockType::Stone;
		}
		else if (Index3D.Z < SurfaceHeight)
		{
			BlockTypes[Index1D] = EBlockType::Dirt;
		}
		else if (Index3D.Z == SurfaceHeight)
		{
			BlockTypes[Index1D] = EBlockType::Grass;
		}
		else
		{
			BlockTypes[Index1D] = EBlockType::Air;
		}

		BlockStates[Index1D] = EBlockState::NoCrack;
	}
}

void AChunk::BuildChunkMesh()
{
	ChunkMesh.Empty();
	
	const FIntVector& BlockCount = FVoxel::BlockCount;
	const int32 BlockSize = FVoxel::BlockSize;
	
	for (int32 z = 0; z < BlockCount.Z; z++)
	{
		for (int32 y = 0; y < BlockCount.Y; y++)
		{
			for (int32 x = 0; x < BlockCount.X; x++)
			{
				int32 Index1D = UVoxelFunctionLibrary::Index3DTo1D(FIntVector(x, y, z), BlockCount);
				UVoxelFunctionLibrary::BuildBlockMesh(this, BlockTypes[Index1D], FIntVector(x, y, z), FVector(x, y, z) * BlockSize);
			}
		}
	}

	ProceduralMeshComponent->ClearAllMeshSections();
	UVoxelFunctionLibrary::CreateMeshSection(0, ProceduralMeshComponent, ChunkMesh);
	ProceduralMeshComponent->SetMaterial(0, Material);
}
