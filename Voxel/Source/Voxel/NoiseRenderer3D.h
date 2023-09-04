#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "NoiseRendererBase.h"
#include "GameFramework/Actor.h"
#include "NoiseRenderer3D.generated.h"

UCLASS()
class VOXEL_API ANoiseRenderer3D : public ANoiseRendererBase
{
	GENERATED_BODY()
	
public:	
	ANoiseRenderer3D();
	
public:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

protected:
	virtual void DrawGraph() override;
	
public:
	UPROPERTY(EditAnywhere, Category="Noise")
	FIntVector BlockCount = FIntVector(20, 20, 20);

private:
	FVoxelNoiseSettings PrevNoiseSettings;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInstancedStaticMeshComponent> InstancedStaticMeshComponent;
};
