#include "VoxelFunctionLibrary.h"

#include "Chunk.h"
#include "Define.h"
#include "ProceduralMeshComponent.h"

void UVoxelFunctionLibrary::BuildQuadMesh(EBlockSide Side, EBlockType Type, const FVector& Offset, FMesh& OutMesh)
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

	OutMesh.UVs.Add(FVoxel::BlockUVs[Type][0]);
	OutMesh.UVs.Add(FVoxel::BlockUVs[Type][1]);
	OutMesh.UVs.Add(FVoxel::BlockUVs[Type][2]);
	OutMesh.UVs.Add(FVoxel::BlockUVs[Type][3]);
	
	switch (Side)
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

void UVoxelFunctionLibrary::BuildBlockMesh(AChunk* Chunk, EBlockType Type, const FIntVector& BlockIndex, const FVector& Offset)
{
	if (Type == Air)
		return;
	
	for (int32 i = 0; i < (int32)EBlockSide::Count; i++)
	{
		EBlockSide Side = static_cast<EBlockSide>(i);
		if (DoesNeedOptimization(Chunk, BlockIndex, Side) == false)
			UVoxelFunctionLibrary::BuildQuadMesh(Side, Type, Offset, Chunk->ChunkMesh);
	}
}

bool UVoxelFunctionLibrary::DoesNeedOptimization(const AChunk* Chunk, const FIntVector& BlockIndex, EBlockSide Side)
{
	const int32 dx[] = { +0, +0, -1, +1, +0, +0 };
	const int32 dy[] = { -1, +1, +0, +0, +0, +0 };
	const int32 dz[] = { +0, +0, +0, +0, -1, +1 };
	
	FIntVector CheckIndex = FIntVector(BlockIndex.X + dx[(int32)Side], BlockIndex.Y + dy[(int32)Side], BlockIndex.Z + dz[(int32)Side]);
	
	if (CheckIndex.X < 0 || CheckIndex.X >= Chunk->BlockCount.X ||
		CheckIndex.Y < 0 || CheckIndex.Y >= Chunk->BlockCount.Y ||
		CheckIndex.Z < 0 || CheckIndex.Z >= Chunk->BlockCount.Z)
		return false;

	int32 Index = Index3DTo1D(CheckIndex, Chunk->BlockCount);
	if (Chunk->ChunkData[Index] == Air || Chunk->ChunkData[Index] == Water)
		return false;
	return true;
}

void UVoxelFunctionLibrary::CreateMeshSection(int32 Index, UProceduralMeshComponent* Component, const FMesh& Mesh)
{
	Component->CreateMeshSection(Index, Mesh.Vertices, Mesh.Triangles, Mesh.Normals, Mesh.UVs, Mesh.VertexColors, Mesh.Tangents, true);
}

float UVoxelFunctionLibrary::FBMNoise(const FVector2D& Location, int32 Octaves, float Scale, float HeightScale, float HeightOffset)
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
