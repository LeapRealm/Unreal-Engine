#pragma once

#include "LyraPlayerCameraManager.generated.h"

#define LYRA_CAMERA_DEFAULT_FOV (80.0f)
#define LYRA_CAMERA_DEFAULT_PITCH_MIN (-89.0f)
#define LYRA_CAMERA_DEFAULT_PITCH_MAX (89.0f)

UCLASS()
class ALyraPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	ALyraPlayerCameraManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
