#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VoxelFunctionLibrary.generated.h"

struct FMesh;
class UProceduralMeshComponent;

UCLASS()
class VOXEL_API UVoxelFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void BuildQuad(EBlockSide Side, EBlockType Type, const FVector& Offset, FMesh& OutMesh);
	static void MergeMeshes(const TArray<FMesh>& Meshes, FMesh& OutMesh);
	static void CreateMeshSection(UProceduralMeshComponent* Component, const FMesh& Mesh);

private:
	static void ExtractArrays(const TMap<FVertex, int32>& VertexToOrder, FMesh& OutMesh);
	static void ClearMesh(FMesh& OutMesh);
};
