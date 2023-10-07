#include "VoxelAnimInstance.h"

#include "VoxelCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UVoxelAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (AVoxelCharacter* VoxelCharacter = Cast<AVoxelCharacter>(TryGetPawnOwner()))
	{
		Pitch = VoxelCharacter->GetControlRotation().Pitch;
		Speed = VoxelCharacter->GetCharacterMovement()->Velocity.Length();
		bShouldMove = Speed > 5.f;

		const FVector2D& LastMoveInputValue = VoxelCharacter->LastMoveInputValue;
		if (LastMoveInputValue == FVector2D::ZeroVector)
		{
			TargetYaw = 0.f;
		}
		else
		{
			FVector2D A = FVector2D(1.f, 0.f).GetSafeNormal();
			FVector2D B = LastMoveInputValue.GetSafeNormal();
			TargetYaw = UKismetMathLibrary::DegAcos(UKismetMathLibrary::DotProduct2D(A, B));
			if (UKismetMathLibrary::CrossProduct2D(A, B) < 0)
				TargetYaw *= -1;

			if (TargetYaw < -90.f)
				TargetYaw += 180.f;
			else if (TargetYaw > 90.f)
				TargetYaw -= 180.f;
			else
				TargetYaw = FMath::Clamp(TargetYaw, -45.f, 45.f);
		}
		
		CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaSeconds, 8.f);
	}
}
