#include "AnimInstanceBase.h"

#include "CreatureBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (ACharacter* Character = Cast<ACreatureBase>(TryGetPawnOwner()))
		CharacterMovementComponent = Character->GetCharacterMovement();
}

void UAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (CharacterMovementComponent)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(CharacterMovementComponent->Velocity);
		bShouldMove = GroundSpeed > 5.f;
	}
}
