#include "LyraCharacter.h"

#include "LyraPawnExtensionComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraCharacter)

ALyraCharacter::ALyraCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;
	
	PawnExtensionComponent = CreateDefaultSubobject<ULyraPawnExtensionComponent>(TEXT("PawnExtensionComponent"));
}
