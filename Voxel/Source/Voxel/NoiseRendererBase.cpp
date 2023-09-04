#include "NoiseRendererBase.h"

ANoiseRendererBase::ANoiseRendererBase()
{
	PrimaryActorTick.bCanEverTick = true;

#if WITH_EDITOR
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(SceneComponent);
#endif
}
