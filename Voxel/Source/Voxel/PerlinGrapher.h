#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerlinGrapher.generated.h"

UCLASS()
class VOXEL_API APerlinGrapher : public AActor
{
	GENERATED_BODY()
	
public:	
	APerlinGrapher();

public:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	int32 PositionCount = 60;
	
	UPROPERTY(EditAnywhere)
	float HeightScale = 10.34;

	UPROPERTY(EditAnywhere)
	float Scale = 0.5f;

	UPROPERTY(EditAnywhere)
	float Octaves = 3.f;

	UPROPERTY(EditAnywhere)
	float HeightOffset = 20.f;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;
};
