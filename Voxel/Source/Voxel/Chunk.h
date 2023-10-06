#pragma once

#include "CoreMinimal.h"
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
	void Init(const FIntVector& NewChunkIndex);
	void BuildChunkMesh();

public:
	FIntVector ChunkIndex;

private:
	FCriticalSection CriticalSection;

public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMaterial> Material;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProceduralMeshComponent> ProceduralMeshComponent;
};
