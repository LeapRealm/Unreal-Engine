#include "Chunk.h"

#include "Define.h"
#include "ProceduralMeshComponent.h"
#include "VoxelFunctionLibrary.h"
#include "VoxelGameMode.h"
#include "Kismet/GameplayStatics.h"

AChunk::AChunk()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProcMesh"));
	ProceduralMeshComponent->bUseAsyncCooking = true;
	SetRootComponent(ProceduralMeshComponent);
	
	static ConstructorHelpers::FObjectFinder<UMaterial> M_Block(TEXT("/Script/Engine.Material'/Game/Materials/M_Block.M_Block'"));
	if (M_Block.Succeeded())
		Material = M_Block.Object;
}

void AChunk::BuildChunkData()
{
	AVoxelGameMode* VoxelGameMode = Cast<AVoxelGameMode>(UGameplayStatics::GetGameMode(this));
	check(VoxelGameMode);
	
	const FIntVector& BlockCount = FVoxel::BlockCount;
	BlockTypes.SetNumUninitialized(BlockCount.X * BlockCount.Y * BlockCount.Z);
	BlockStates.SetNumUninitialized(BlockCount.X * BlockCount.Y * BlockCount.Z);

	float CaveRandValue = FMath::RandRange(0.f, 100.f);
	
	for (int32 Index1D = 0; Index1D < BlockTypes.Num(); Index1D++)
	{
		BlockStates[Index1D] = EBlockState::NoCrack;
		
		FIntVector Index3D = UVoxelFunctionLibrary::Index1DTo3D(Index1D, BlockCount);
		Index3D += (ChunkIndex * BlockCount);

		if (Index3D.Z == 0)
		{
			BlockTypes[Index1D] = EBlockType::BedRock;
			continue;
		}
		
		int32 SurfaceHeight = static_cast<int32>(UVoxelFunctionLibrary::FastNoise2D(VoxelGameMode->SurfaceNoiseWrapper, 
			FVector2D(Index3D.X, Index3D.Y), VoxelGameMode->SurfaceNoiseSettings));
		
		int32 StoneHeight = SurfaceHeight - FVoxel::StoneHeightOffset;
		
		if (CaveRandValue <= FVoxel::CavePercent && Index3D.Z < StoneHeight && Index3D.Z > FVoxel::DiamondHeightMin)
		{
			const FPerlinNoiseSettings& CaveSettings = VoxelGameMode->CaveNoiseSettings;
			int32 CaveDig = static_cast<int32>(UVoxelFunctionLibrary::FBMNoise3D(FVector(Index3D),
				CaveSettings.Octaves, CaveSettings.Scale, CaveSettings.HeightScale, CaveSettings.HeightOffset));
			
			if (CaveDig < CaveSettings.DrawCutOff)
			{
				BlockTypes[Index1D] = EBlockType::Air;
				continue;
			}
		}
		
		if (Index3D.Z < FVoxel::DiamondHeightMin)
		{
			BlockTypes[Index1D] = EBlockType::Stone;
		}
		else if (Index3D.Z < FVoxel::DiamondHeightMax)
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
}

void AChunk::CreateChunkMesh()
{
	ProceduralMeshComponent->ClearAllMeshSections();
	UVoxelFunctionLibrary::CreateMeshSection(0, ProceduralMeshComponent, ChunkMesh);
	ProceduralMeshComponent->SetMaterial(0, Material);
}

void AChunk::UpdateChunkMesh()
{
	UVoxelFunctionLibrary::UpdateMeshSection(0, ProceduralMeshComponent, ChunkMesh);
}
