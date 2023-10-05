#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VoxelFunctionLibrary.generated.h"

class AChunk;
class AVoxelGameMode;
class UFastNoiseWrapper;
class UProceduralMeshComponent;

UCLASS()
class VOXEL_API UVoxelFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void BuildChunkData(UFastNoiseWrapper* SurfaceNoiseWrapper, const FIntVector& ChunkIndex3D, FChunkData& ChunkData);
	
	static void BuildQuadMesh(ESide BlockSide, EBlockTextureType TextureType, const FVector& Offset, FMesh& OutMesh);
	static void BuildBlockMesh(const FIntVector& ChunkIndex, FMesh& ChunkMesh, EBlockType BlockType, const FIntVector& BlockIndex, const FVector& Offset);
	static bool DoesNeedOptimization(const FIntVector& ChunkIndex, const FIntVector& BlockIndex, ESide BlockSide);

	static EBlockTextureType GetTextureType(ESide BlockSide, EBlockType BlockType);
	
	static void CreateMeshSection(int32 Index, UProceduralMeshComponent* Component, const FMesh& Mesh);
	
	static float FBMNoise2D(const FVector2D& Location, int32 Octaves, float Scale, float HeightScale, float HeightOffset);
	static float FBMNoise3D(const FVector& Location, int32 Octaves, float Scale, float HeightScale, float HeightOffset);
	static float FastNoise2D(UFastNoiseWrapper* FastNoiseWrapper, const FVector2D& Location, const FFastNoiseSettings& FastNoiseSettings);

	static int32 Index3DTo1D(const FIntVector& Index, const FIntVector& Count);
	static FIntVector Index1DTo3D(int32 Index, const FIntVector& BlockCount);
	
	static FIntVector WorldPosToChunkIndex(const FVector& WorldPos);
	static FIntVector WorldPosToBlockIndex(const FVector& WorldPos);

	static FVector GetBlockCenterWorldPos(const FIntVector& ChunkIndex3D, const FIntVector& BlockIndex3D);
};
