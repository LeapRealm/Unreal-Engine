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
	void InitInvisibleWalls();
	void InitNoise();
	void InitChunks();
	void SpawnChunks();
	
public:
	void UpdateBlockType(const FIntVector& ChunkIndex3D, const FIntVector& BlockIndex3D, EBlockType NewBlockType);
	
public:
	UPROPERTY(EditAnywhere)
	int32 Seed = 1337;

public:
	UPROPERTY(VisibleAnywhere)
	TArray<FChunkData> ChunkDatas;
	
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<AChunk>> Chunks;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UFastNoiseWrapper> SurfaceNoiseWrapper;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AVoxelCharacter> VoxelCharacter;

private:
	std::atomic<int32> BuiltChunkDataCount = 0;
};
