#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "GameFramework/GameModeBase.h"
#include "VoxelGameMode.generated.h"

class AChunk;
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
	void BuildChunks();

public:
	FFastNoiseSettings SurfaceNoiseSettings = {EFastNoise_NoiseType::SimplexFractal, 0.007, 5, 1.6, 0.5, 30, 220};
	FPerlinNoiseSettings CaveNoiseSettings = {0.1, 2, 2, 1, 0.25};
	
public:
	UPROPERTY(EditAnywhere)
	int32 Seed = 1337;

public:
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<AChunk>> Chunks;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UFastNoiseWrapper> SurfaceNoiseWrapper;
};
