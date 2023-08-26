#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VoxelGameMode.generated.h"

class AChunk;

UCLASS()
class VOXEL_API AVoxelGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
public:
	FIntVector ChunkCount = FIntVector(10, 10, 10);
	FIntVector BlockCount = FIntVector(10, 10, 10);
	float BlockSize = 100.f;

public:
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<AChunk>> Chunks;
};
