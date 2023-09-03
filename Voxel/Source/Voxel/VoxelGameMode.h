#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "GameFramework/GameModeBase.h"
#include "VoxelGameMode.generated.h"

class AGraphRenderer;
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
	inline static FGraphSettings SurfaceGraphSettings;
	inline static FGraphSettings MixedGraphSettings;
	inline static FGraphSettings StoneGraphSettings;
	
public:
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<AChunk>> Chunks;
};
