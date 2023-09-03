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
	TArray<EBlockType> ChunkData;
	FIntVector ChunkIndex;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMaterial> Material;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProceduralMeshComponent> ProceduralMeshComponent;
};
