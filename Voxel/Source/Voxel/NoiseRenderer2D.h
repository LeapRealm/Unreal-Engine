#pragma once

#include "CoreMinimal.h"
#include "NoiseRendererBase.h"
#include "GameFramework/Actor.h"
#include "NoiseRenderer2D.generated.h"

UCLASS()
class VOXEL_API ANoiseRenderer2D : public ANoiseRendererBase
{
	GENERATED_BODY()
	
public:	
	ANoiseRenderer2D();

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override { return true; }

protected:
	virtual void DrawGraph() override;
	
public:
	UPROPERTY(EditAnywhere, Category="Noise")
	int32 PositionCount = 100;

	UPROPERTY(EditAnywhere, Category="Noise")
	FLinearColor Color = FLinearColor::Red;

	UPROPERTY(EditAnywhere, Category="Noise")
	float LineThickness = 20.f;
	
private:
	const float TickTime = 0.1f;
	float PassedTime = 0.f;
};
