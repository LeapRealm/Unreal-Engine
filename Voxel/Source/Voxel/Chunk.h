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
	void BuildChunkData(); 
	void BuildChunkMesh();
	
	void CreateChunkMesh();
	void UpdateChunkMesh();

public:
	void SetChunkIndex(const FIntVector& InChunkIndex) { ChunkIndex = InChunkIndex; }
	
public:
	FMesh ChunkMesh;
	FIntVector ChunkIndex;
	TArray<EBlockType> BlockTypes;
	TArray<EBlockState> BlockStates;
	
public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMaterial> Material;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProceduralMeshComponent> ProceduralMeshComponent;
};
