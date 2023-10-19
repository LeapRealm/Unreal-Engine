#pragma once

#include "GameFramework/Character.h"
#include "LyraCharacter.generated.h"

UCLASS()
class ALyraCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	ALyraCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
