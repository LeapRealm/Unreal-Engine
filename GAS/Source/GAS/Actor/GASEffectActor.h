#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GASEffectActor.generated.h"

class USphereComponent;

UCLASS()
class GAS_API AGASEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AGASEffectActor();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
};
