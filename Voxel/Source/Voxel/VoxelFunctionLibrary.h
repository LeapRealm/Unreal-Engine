#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VoxelFunctionLibrary.generated.h"

struct FMesh;
class AChunk;
class UProceduralMeshComponent;

UCLASS()
class VOXEL_API UVoxelFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void BuildQuadMesh(EBlockSide Side, EBlockType Type, const FVector& Offset, FMesh& OutMesh);
	static void BuildBlockMesh(AChunk* Chunk, EBlockType Type, const FIntVector& BlockIndex, const FVector& Offset);
	static bool DoesNeedOptimization(const AChunk* Chunk, const FIntVector& BlockIndex, EBlockSide Side);
	static void CreateMeshSection(int32 Index, UProceduralMeshComponent* Component, const FMesh& Mesh);

	static float FBMNoise(const FVector2D& Location, int32 Octaves, float Scale, float HeightScale, float HeightOffset);

	static int32 Index3DTo1D(const FIntVector& Index, const FIntVector& BlockCount);
	static FIntVector Index1DTo3D(int32 Index, const FIntVector& BlockCount);
};