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
	float HeightScale = 5.887208f;
	float Scale = 0.001f;
	int32 Octaves = 8;
	float HeightOffset = 20.f;

public:
	FMesh ChunkMesh;
	TArray<TEnumAsByte<EBlockType>> ChunkData;

public:
	FIntVector ChunkIndex;
	FIntVector BlockCount;
	float BlockSize;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMaterial> Material;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProceduralMeshComponent> ProceduralMeshComponent;
};
