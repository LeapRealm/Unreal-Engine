#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "GameFramework/GameModeBase.h"
#include "VoxelGameMode.generated.h"

class ANoiseRenderer2D;
class AChunk;

UCLASS()
class VOXEL_API AVoxelGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AVoxelGameMode();
	
public:
	virtual void BeginPlay() override;
	
public:
	inline static FVoxelNoiseSettings SurfaceNoiseSettings;
	inline static FVoxelNoiseSettings StoneNoiseSettings;
	inline static FVoxelNoiseSettings DiamondTopNoiseSettings;
	inline static FVoxelNoiseSettings DiamondBottomNoiseSettings;
	
public:
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<AChunk>> Chunks;
};
