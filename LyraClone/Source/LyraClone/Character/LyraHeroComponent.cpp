#include "LyraHeroComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraHeroComponent)

ULyraHeroComponent::ULyraHeroComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}
