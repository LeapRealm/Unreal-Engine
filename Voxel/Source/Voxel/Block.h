#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

class UProceduralMeshComponent;

UCLASS()
class VOXEL_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlock();

public:	
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterial> Material;
	
private:
	TObjectPtr<UProceduralMeshComponent> ProceduralMeshComponent;
};
