#include "LyraCharacter.h"

#include "LyraPawnExtensionComponent.h"
#include "LyraClone/Camera/LyraCameraComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraCharacter)

ALyraCharacter::ALyraCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;
	
	PawnExtensionComponent = CreateDefaultSubobject<ULyraPawnExtensionComponent>(TEXT("PawnExtensionComponent"));

	CameraComponent = CreateDefaultSubobject<ULyraCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetRelativeLocation(FVector(-300.f, 0.f, 75.f));
}

void ALyraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Pawn에 Possess하고 난 뒤 Controller와 PlayerState가 준비되었으니 InitState를 계속 진행합니다.
	PawnExtensionComponent->SetupPlayerInputComponent();
}
