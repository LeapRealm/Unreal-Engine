#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Define.h"
#include "CrackDecalBox.generated.h"

UCLASS()
class VOXEL_API ACrackDecalBox : public AActor
{
	GENERATED_BODY()
	
public:	
	ACrackDecalBox();

protected:
	virtual void BeginPlay() override;
	
public:
	void SetVisibility(EBlockState BlockState);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMaterial> Material;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMaterialInstanceDynamic> MaterialInstanceDynamic;
};
