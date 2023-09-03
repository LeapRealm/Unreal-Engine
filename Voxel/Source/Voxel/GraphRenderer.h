#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "GameFramework/Actor.h"
#include "GraphRenderer.generated.h"

UCLASS()
class VOXEL_API AGraphRenderer : public AActor
{
	GENERATED_BODY()
	
public:	
	AGraphRenderer();

public:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

private:
	void DrawGraph();
	
public:
	UPROPERTY(EditAnywhere)
	EGraphRendererType Type = EGraphRendererType::None;
	
	UPROPERTY(EditAnywhere)
	int32 PositionCount = 100;
	
	UPROPERTY(EditAnywhere)
	FGraphSettings GraphSettings = { 0.001f, 5.887208f, 8, 20.f, 1.f };

	UPROPERTY(EditAnywhere)
	FLinearColor Color = FLinearColor::Red;

	UPROPERTY(EditAnywhere)
	float LineThickness = 10.f;
	
private:
	FTimerHandle TimerHandle;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;
};
