#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "GameFramework/Actor.h"
#include "Chunk.generated.h"

class UProceduralMeshComponent;

UCLASS()
class VOXEL_API AChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	AChunk();

public:
	void Init(const FIntVector& InChunkIndex);

private:
	void BuildChunkData(); 
	void BuildChunkMesh();

public:
	FMesh ChunkMesh;
	FIntVector ChunkIndex;
	TArray<EBlockType> BlockTypes;
	TArray<EBlockState> BlockStates;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMaterial> Material;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProceduralMeshComponent> ProceduralMeshComponent;
};
