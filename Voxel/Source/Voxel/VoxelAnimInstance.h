#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "VoxelAnimInstance.generated.h"

UCLASS()
class VOXEL_API UVoxelAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Pitch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentYaw;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TargetYaw;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bShouldMove;
};
