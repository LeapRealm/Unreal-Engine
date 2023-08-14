#include "FrameworkGameMode.h"

#include "Creature/PlayerBase.h"
#include "Creature/PlayerControllerBase.h"

AFrameworkGameMode::AFrameworkGameMode()
{
	DefaultPawnClass = APlayerBase::StaticClass();
	PlayerControllerClass = APlayerControllerBase::StaticClass();
}

void AFrameworkGameMode::BeginPlay()
{
	Super::BeginPlay();
}
