#include "LyraPlayerController.h"

#include "LyraClone/Camera/LyraPlayerCameraManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraPlayerController)

ALyraPlayerController::ALyraPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    PlayerCameraManagerClass = ALyraPlayerCameraManager::StaticClass();
}
