#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "GameFramework/GameModeBase.h"
#include "VoxelGameMode.generated.h"

class AChunk;
class AVoxelCharacter;
class UFastNoiseWrapper;

UCLASS()
class VOXEL_API AVoxelGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AVoxelGameMode();
	
public:
	virtual void BeginPlay() override;
	
private:
	void InitNoise();
	void InitChunks();

	void CullingChunks();
	void DestroyFarChunks(const FIntVector& MinCullIndex, const FIntVector& MaxCullIndex);
	void SpawnNearChunks(const FIntVector& MinCullIndex, const FIntVector& MaxCullIndex);

public:
	void UpdateBlockType(const FIntVector& ChunkIndex3D, const FIntVector& BlockIndex3D, EBlockType NewBlockType);
	void UpdateBlockState(const FIntVector& ChunkIndex3D, const FIntVector& BlockIndex3D, EBlockState NewBlockState);

public:
	UPROPERTY(EditAnywhere)
	int32 Seed = 1337;

public:
	UPROPERTY(EditAnywhere)
	bool bCullEnable = false;
	
	UPROPERTY(EditAnywhere)
	float CullingChunksTimerRate = 1.f;

	UPROPERTY(EditAnywhere)
	int32 CullIndexDistance = 3;

	UPROPERTY(VisibleAnywhere)
	FIntVector PlayerChunkIndex;
	
public:
	UPROPERTY(VisibleAnywhere)
	TArray<FChunkData> ChunkDatas;
	
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<AChunk>> Chunks;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<AChunk>> SpawnedChunks;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UFastNoiseWrapper> SurfaceNoiseWrapper;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AVoxelCharacter> VoxelCharacter;

private:
	bool bBuildChunkDataCompleted = false;
	FTimerHandle CullingChunksTimerHandle;
	std::atomic<int32> BuiltChunkDataCount;
};
