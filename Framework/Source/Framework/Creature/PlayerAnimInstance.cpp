#include "Creature/PlayerAnimInstance.h"

#include "CreatureBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (ACharacter* Character = Cast<ACreatureBase>(TryGetPawnOwner()))
		CharacterMovementComponent = Character->GetCharacterMovement();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (CharacterMovementComponent)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(CharacterMovementComponent->Velocity);
		bShouldMove = GroundSpeed > 5.f;
	}
}
