#include "VoxelFunctionLibrary.h"

#include "Chunk.h"
#include "Define.h"
#include "ProceduralMeshComponent.h"
#include "VoxelGameMode.h"
#include "Kismet/GameplayStatics.h"

void UVoxelFunctionLibrary::BuildChunkData(UFastNoiseWrapper* SurfaceNoiseWrapper, const FIntVector& ChunkIndex, FChunkData& ChunkData)
{
	const FIntVector& BlockCount = FVoxel::BlockCount;

	TArray<EBlockType>& BlockTypes = ChunkData.BlockTypes;
	TArray<EBlockState>& BlockStates = ChunkData.BlockStates;
	
	float CaveRandValue = FMath::RandRange(0.f, 100.f);
	
	for (int32 LocalBlockIndex1D = 0; LocalBlockIndex1D < BlockTypes.Num(); LocalBlockIndex1D++)
	{
		BlockStates[LocalBlockIndex1D] = EBlockState::NoCrack;
		
		const FIntVector WorldBlockIndex3D = UVoxelFunctionLibrary::Index1DTo3D(LocalBlockIndex1D, BlockCount) + (ChunkIndex * BlockCount);

		if (WorldBlockIndex3D.Z == 0)
		{
			BlockTypes[LocalBlockIndex1D] = EBlockType::BedRock;
			continue;
		}
		
		int32 SurfaceHeight = static_cast<int32>(UVoxelFunctionLibrary::FastNoise2D(SurfaceNoiseWrapper, 
			FVector2D(WorldBlockIndex3D.X, WorldBlockIndex3D.Y), FVoxel::SurfaceNoiseSettings));
		
		int32 StoneHeight = SurfaceHeight - FVoxel::StoneHeightOffset;
		
		if (CaveRandValue <= FVoxel::CavePercent && WorldBlockIndex3D.Z < StoneHeight && WorldBlockIndex3D.Z > FVoxel::DiamondHeightMin)
		{
			const FPerlinNoiseSettings& CaveSettings = FVoxel::CaveNoiseSettings;
			int32 CaveDig = static_cast<int32>(UVoxelFunctionLibrary::FBMNoise3D(FVector(WorldBlockIndex3D),
				CaveSettings.Octaves, CaveSettings.Scale, CaveSettings.HeightScale, CaveSettings.HeightOffset));
			
			if (CaveDig < CaveSettings.DrawCutOff)
			{
				BlockTypes[LocalBlockIndex1D] = EBlockType::Air;
				continue;
			}
		}
		
		if (WorldBlockIndex3D.Z < FVoxel::DiamondHeightMin)
		{
			BlockTypes[LocalBlockIndex1D] = EBlockType::Stone;
		}
		else if (WorldBlockIndex3D.Z < FVoxel::DiamondHeightMax)
		{
			float Percent = 0.f;
			float RandValue = FMath::RandRange(0.f, 100.f);
			
			if (RandValue <= (Percent += FVoxel::IronPercent))
				BlockTypes[LocalBlockIndex1D] = EBlockType::Iron;
			else if (RandValue <= (Percent += FVoxel::DiamondPercent))
				BlockTypes[LocalBlockIndex1D] = EBlockType::Diamond;
			else
				BlockTypes[LocalBlockIndex1D] = EBlockType::Stone;
		}
		else if (WorldBlockIndex3D.Z < StoneHeight)
		{
			float Percent = 0.f;
			float RandValue = FMath::RandRange(0.f, 100.f);
			
			if (RandValue <= (Percent += FVoxel::CoalPercent))
				BlockTypes[LocalBlockIndex1D] = EBlockType::Coal;
			else if (RandValue <= (Percent += FVoxel::IronPercent))
				BlockTypes[LocalBlockIndex1D] = EBlockType::Iron;
			else if (RandValue <= (Percent += FVoxel::GoldPercent))
				BlockTypes[LocalBlockIndex1D] = EBlockType::Gold;
			else
				BlockTypes[LocalBlockIndex1D] = EBlockType::Stone;
		}
		else if (WorldBlockIndex3D.Z < (StoneHeight + SurfaceHeight) / 2)
		{
			float RandValue = FMath::RandRange(0.f, 100.f);
			
			if (RandValue <= 50.f)
				BlockTypes[LocalBlockIndex1D] = EBlockType::Dirt;
			else
				BlockTypes[LocalBlockIndex1D] = EBlockType::Stone;
		}
		else if (WorldBlockIndex3D.Z < SurfaceHeight)
		{
			BlockTypes[LocalBlockIndex1D] = EBlockType::Dirt;
		}
		else if (WorldBlockIndex3D.Z == SurfaceHeight)
		{
			BlockTypes[LocalBlockIndex1D] = EBlockType::Grass;
		}
		else
		{
			BlockTypes[LocalBlockIndex1D] = EBlockType::Air;
		}
	}
}

void UVoxelFunctionLibrary::BuildQuadMesh(EBlockSide BlockSide, EBlockTextureType TextureType, const FVector& Offset, FMesh& OutMesh)
{
	const FVector FLU = FVoxel::FLU + Offset;
	const FVector FRU = FVoxel::FRU + Offset;
	const FVector FLD = FVoxel::FLD + Offset;
	const FVector FRD = FVoxel::FRD + Offset;
	const FVector BLU = FVoxel::BLU + Offset;
	const FVector BRU = FVoxel::BRU + Offset;
	const FVector BLD = FVoxel::BLD + Offset;
	const FVector BRD = FVoxel::BRD + Offset;

	int32 VertexNum = OutMesh.Vertices.Num();
	OutMesh.Triangles.Append({ VertexNum + 0, VertexNum + 2, VertexNum + 1, VertexNum + 1, VertexNum + 2, VertexNum + 3 });

	OutMesh.UVs.Add(FVoxel::BlockTextureUVs[static_cast<int32>(TextureType)][0]);
	OutMesh.UVs.Add(FVoxel::BlockTextureUVs[static_cast<int32>(TextureType)][1]);
	OutMesh.UVs.Add(FVoxel::BlockTextureUVs[static_cast<int32>(TextureType)][2]);
	OutMesh.UVs.Add(FVoxel::BlockTextureUVs[static_cast<int32>(TextureType)][3]);
	
	switch (BlockSide)
	{
	case EBlockSide::Forward:
		OutMesh.Vertices.Add(FRU);
		OutMesh.Vertices.Add(FLU);
		OutMesh.Vertices.Add(FRD);
		OutMesh.Vertices.Add(FLD);

		OutMesh.Normals.Add(FVector::ForwardVector);
		OutMesh.Normals.Add(FVector::ForwardVector);
		OutMesh.Normals.Add(FVector::ForwardVector);
		OutMesh.Normals.Add(FVector::ForwardVector);
		break;
	case EBlockSide::Backward:
		OutMesh.Vertices.Add(BLU);
		OutMesh.Vertices.Add(BRU);
		OutMesh.Vertices.Add(BLD);
		OutMesh.Vertices.Add(BRD);

		OutMesh.Normals.Add(FVector::BackwardVector);
		OutMesh.Normals.Add(FVector::BackwardVector);
		OutMesh.Normals.Add(FVector::BackwardVector);
		OutMesh.Normals.Add(FVector::BackwardVector);
		break;
	case EBlockSide::Down:
		OutMesh.Vertices.Add(BLD);
		OutMesh.Vertices.Add(BRD);
		OutMesh.Vertices.Add(FLD);
		OutMesh.Vertices.Add(FRD);

		OutMesh.Normals.Add(FVector::DownVector);
		OutMesh.Normals.Add(FVector::DownVector);
		OutMesh.Normals.Add(FVector::DownVector);
		OutMesh.Normals.Add(FVector::DownVector);
		break;
	case EBlockSide::Up:
		OutMesh.Vertices.Add(BRU);
		OutMesh.Vertices.Add(BLU);
		OutMesh.Vertices.Add(FRU);
		OutMesh.Vertices.Add(FLU);

		OutMesh.Normals.Add(FVector::UpVector);
		OutMesh.Normals.Add(FVector::UpVector);
		OutMesh.Normals.Add(FVector::UpVector);
		OutMesh.Normals.Add(FVector::UpVector);
		break;
	case EBlockSide::Left:
		OutMesh.Vertices.Add(FLU);
		OutMesh.Vertices.Add(BLU);
		OutMesh.Vertices.Add(FLD);
		OutMesh.Vertices.Add(BLD);

		OutMesh.Normals.Add(FVector::LeftVector);
		OutMesh.Normals.Add(FVector::LeftVector);
		OutMesh.Normals.Add(FVector::LeftVector);
		OutMesh.Normals.Add(FVector::LeftVector);
		break;
	case EBlockSide::Right:
		OutMesh.Vertices.Add(BRU);
		OutMesh.Vertices.Add(FRU);
		OutMesh.Vertices.Add(BRD);
		OutMesh.Vertices.Add(FRD);

		OutMesh.Normals.Add(FVector::RightVector);
		OutMesh.Normals.Add(FVector::RightVector);
		OutMesh.Normals.Add(FVector::RightVector);
		OutMesh.Normals.Add(FVector::RightVector);
		break;
	}
}

void UVoxelFunctionLibrary::BuildBlockMesh(AChunk* Chunk, EBlockType BlockType, const FIntVector& BlockIndex, const FVector& Offset)
{
	if (BlockType == EBlockType::Air)
		return;

	const int32 BlockSideCount = static_cast<int32>(EBlockSide::Count);
	for (int32 i = 0; i < BlockSideCount; i++)
	{
		EBlockSide BlockSide = static_cast<EBlockSide>(i);
		if (DoesNeedOptimization(Chunk, BlockIndex, BlockSide) == false)
			UVoxelFunctionLibrary::BuildQuadMesh(BlockSide, GetTextureType(BlockSide, BlockType), Offset, Chunk->ChunkMesh);
	}
}

bool UVoxelFunctionLibrary::DoesNeedOptimization(const AChunk* Chunk, const FIntVector& BlockIndex, EBlockSide BlockSide)
{
	AVoxelGameMode* VoxelGameMode = Cast<AVoxelGameMode>(UGameplayStatics::GetGameMode(Chunk));
	if (VoxelGameMode == nullptr)
		return false;
	
	FIntVector CheckBlockIndex3D = FIntVector(
		BlockIndex.X + FVoxel::DX[static_cast<int32>(BlockSide)],
		BlockIndex.Y + FVoxel::DY[static_cast<int32>(BlockSide)],
		BlockIndex.Z + FVoxel::DZ[static_cast<int32>(BlockSide)]
	);

	const FIntVector& BlockCount = FVoxel::BlockCount;
	const FIntVector& ChunkCount = FVoxel::ChunkCount;

	EBlockType BlockType;
	
	if (CheckBlockIndex3D.X < 0 || CheckBlockIndex3D.X >= BlockCount.X ||
		CheckBlockIndex3D.Y < 0 || CheckBlockIndex3D.Y >= BlockCount.Y ||
		CheckBlockIndex3D.Z < 0 || CheckBlockIndex3D.Z >= BlockCount.Z)
	{
		CheckBlockIndex3D.X = (CheckBlockIndex3D.X + BlockCount.X) % BlockCount.X;
		CheckBlockIndex3D.Y = (CheckBlockIndex3D.Y + BlockCount.Y) % BlockCount.Y;
		CheckBlockIndex3D.Z = (CheckBlockIndex3D.Z + BlockCount.Z) % BlockCount.Z;
		
		FIntVector CheckChunkIndex3D = FIntVector(
			Chunk->ChunkIndex.X + FVoxel::DX[static_cast<int32>(BlockSide)],
			Chunk->ChunkIndex.Y + FVoxel::DY[static_cast<int32>(BlockSide)],
			Chunk->ChunkIndex.Z + FVoxel::DZ[static_cast<int32>(BlockSide)]
		);

		if (CheckChunkIndex3D.X < 0 || CheckChunkIndex3D.X >= ChunkCount.X ||
			CheckChunkIndex3D.Y < 0 || CheckChunkIndex3D.Y >= ChunkCount.Y ||
			CheckChunkIndex3D.Z < 0 || CheckChunkIndex3D.Z >= ChunkCount.Z)
			return false;
		
		const FChunkData& CheckChunkData = VoxelGameMode->ChunkDatas[Index3DTo1D(CheckChunkIndex3D, ChunkCount)];
		BlockType = CheckChunkData.BlockTypes[Index3DTo1D(CheckBlockIndex3D, BlockCount)];
	}
	else
	{
		const FChunkData& CheckChunkData = VoxelGameMode->ChunkDatas[Index3DTo1D(Chunk->ChunkIndex, ChunkCount)];
		BlockType = CheckChunkData.BlockTypes[Index3DTo1D(CheckBlockIndex3D, BlockCount)];
	}

	if (BlockType == EBlockType::Air || BlockType == EBlockType::Water)
		return false;
	return true;
}

EBlockTextureType UVoxelFunctionLibrary::GetTextureType(EBlockSide BlockSide, EBlockType BlockType)
{
	EBlockTextureType TextureType = EBlockTextureType::Dirt;

	if (BlockType == EBlockType::Grass)
	{
		switch (BlockSide)
		{
		case EBlockSide::Left:
		case EBlockSide::Right:
		case EBlockSide::Backward:
		case EBlockSide::Forward:
			TextureType = EBlockTextureType::GrassSide;
			break;
		case EBlockSide::Down:
			TextureType = EBlockTextureType::Dirt;
			break;
		case EBlockSide::Up:
			TextureType = EBlockTextureType::GrassTop;
			break;
		}
	}
	else
	{
		switch (BlockType)
		{
		case EBlockType::Dirt:		TextureType = EBlockTextureType::Dirt;		break;
		case EBlockType::Stone:		TextureType = EBlockTextureType::Stone;		break;
		case EBlockType::Sand:		TextureType = EBlockTextureType::Sand;		break;
		case EBlockType::Coal:		TextureType = EBlockTextureType::Coal;		break;
		case EBlockType::Iron:		TextureType = EBlockTextureType::Iron;		break;
		case EBlockType::Gold:		TextureType = EBlockTextureType::Gold;		break;
		case EBlockType::Diamond:	TextureType = EBlockTextureType::Diamond;	break;
		case EBlockType::BedRock:	TextureType = EBlockTextureType::BedRock;	break;
		case EBlockType::Water:		TextureType = EBlockTextureType::Water;		break;
		}
	}

	return TextureType;
}

void UVoxelFunctionLibrary::CreateMeshSection(int32 Index, UProceduralMeshComponent* Component, const FMesh& Mesh)
{
	Component->CreateMeshSection(Index, Mesh.Vertices, Mesh.Triangles, Mesh.Normals, Mesh.UVs, Mesh.VertexColors, Mesh.Tangents, true);
}

void UVoxelFunctionLibrary::UpdateMeshSection(int32 Index, UProceduralMeshComponent* Component, const FMesh& Mesh)
{
	Component->UpdateMeshSection(Index, Mesh.Vertices, Mesh.Normals, Mesh.UVs, Mesh.VertexColors, Mesh.Tangents);
}

float UVoxelFunctionLibrary::FBMNoise2D(const FVector2D& Location, int32 Octaves, float Scale, float HeightScale, float HeightOffset)
{
	float Total = 0.f;
	float Frequency = 1.f;
	for (int32 i = 0; i < Octaves; i++)
	{
		Total += FMath::PerlinNoise2D(FVector2D(Location.X * Scale * Frequency, Location.Y * Scale * Frequency)) * HeightScale;
		Frequency *= 2;
	}
	return Total + HeightOffset;
}

float UVoxelFunctionLibrary::FBMNoise3D(const FVector& Location, int32 Octaves, float Scale, float HeightScale, float HeightOffset)
{
	float Total = 0.f;
	float Frequency = 1.f;
	for (int32 i = 0; i < Octaves; i++)
	{
		Total += FMath::PerlinNoise3D(FVector(Location.X * Scale * Frequency, Location.Y * Scale * Frequency, Location.Z * Scale * Frequency)) * HeightScale;
		Frequency *= 2;
	}
	return Total + HeightOffset;
}

float UVoxelFunctionLibrary::FastNoise2D(UFastNoiseWrapper* FastNoiseWrapper, const FVector2D& Location, const FFastNoiseSettings& FastNoiseSettings)
{
	return FastNoiseWrapper->GetNoise2D(Location.X, Location.Y) * FastNoiseSettings.HeightScale + FastNoiseSettings.HeightOffset;
}

int32 UVoxelFunctionLibrary::Index3DTo1D(const FIntVector& Index, const FIntVector& BlockCount)
{
	return (Index.Z * BlockCount.X * BlockCount.Y) + (Index.Y * BlockCount.X) + Index.X;
}

FIntVector UVoxelFunctionLibrary::Index1DTo3D(int32 Index, const FIntVector& BlockCount)
{
	int32 Z = Index / (BlockCount.X * BlockCount.Y);
	Index -= (Z * BlockCount.X * BlockCount.Y);
	int32 Y = Index / BlockCount.X;
	int32 X = Index % BlockCount.X;
	return FIntVector(X, Y, Z);
}

FIntVector UVoxelFunctionLibrary::WorldPosToChunkIndex(FVector WorldPos)
{
	if (WorldPos.X < 0 || WorldPos.Y < 0 || WorldPos.Z < 0)
		return FIntVector::ZeroValue;
	
	const FIntVector& BlockCount = FVoxel::BlockCount;
	const FIntVector& ChunkCount = FVoxel::ChunkCount;
	float BlockSize = FVoxel::BlockSize;
	FVector ChunkSize = FVector(BlockCount.X * BlockSize, BlockCount.Y * BlockSize, BlockCount.Z * BlockSize);
	
	FIntVector ChunkIndex = FIntVector(WorldPos / ChunkSize);
	if (ChunkIndex.X >= ChunkCount.X || ChunkIndex.Y >= ChunkCount.Y || ChunkIndex.Z >= ChunkCount.Z)
		return FIntVector::ZeroValue;
	
	return ChunkIndex;
}
