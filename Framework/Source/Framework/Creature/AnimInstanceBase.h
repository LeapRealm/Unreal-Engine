#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceBase.generated.h"

class UCharacterMovementComponent;

UCLASS()
class FRAMEWORK_API UAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float GroundSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool bShouldMove = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;
};
