#include "LyraPlayerCameraManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraPlayerCameraManager)

ALyraPlayerCameraManager::ALyraPlayerCameraManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    DefaultFOV = LYRA_CAMERA_DEFAULT_FOV;
	ViewPitchMin = LYRA_CAMERA_DEFAULT_PITCH_MIN;
	ViewPitchMax = LYRA_CAMERA_DEFAULT_PITCH_MAX;
}
