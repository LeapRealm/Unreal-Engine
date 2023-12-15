#pragma once

#include "ModularPlayerController.h"
#include "LyraPlayerController.generated.h"

UCLASS()
class ALyraPlayerController : public AModularPlayerController
{
	GENERATED_BODY()
	
public:
	ALyraPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
