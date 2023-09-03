#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "GameFramework/Actor.h"
#include "NoiseRenderer2D.generated.h"

UCLASS()
class VOXEL_API ANoiseRenderer2D : public AActor
{
	GENERATED_BODY()
	
public:	
	ANoiseRenderer2D();

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override { return true; }

private:
	void DrawGraph();
	
public:
	UPROPERTY(EditAnywhere)
	ENoiseRendererType Type = ENoiseRendererType::None;
	
	UPROPERTY(EditAnywhere)
	int32 PositionCount = 100;
	
	UPROPERTY(EditAnywhere)
	FVoxelNoiseSettings NoiseSettings = { 0.001f, 5.887208f, 8, 20.f };

	UPROPERTY(EditAnywhere)
	FLinearColor Color = FLinearColor::Red;

	UPROPERTY(EditAnywhere)
	float LineThickness = 20.f;
	
private:
	const float TickTime = 0.1f;
	float PassedTime = 0.f;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;
};
