#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "GameFramework/Actor.h"
#include "NoiseRendererBase.generated.h"

UCLASS()
class VOXEL_API ANoiseRendererBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ANoiseRendererBase();

protected:
	virtual void DrawGraph() { }

public:
	UPROPERTY(EditAnywhere, Category="Noise")
	ENoiseRendererType Type = ENoiseRendererType::None;

	UPROPERTY(EditAnywhere, Category="Noise")
	FVoxelNoiseSettings NoiseSettings;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;
};
