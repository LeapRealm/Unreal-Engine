#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockingBox.generated.h"

class UBoxComponent;

UCLASS()
class VOXEL_API ABlockingBox : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlockingBox();

public:
	void SetBoxExtent(const FVector& BoxExtent);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;
};
