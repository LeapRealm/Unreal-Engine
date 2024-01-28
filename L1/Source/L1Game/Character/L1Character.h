#pragma once

#include "GameFramework/Character.h"
#include "L1Character.generated.h"

UCLASS()
class AL1Character : public ACharacter
{
	GENERATED_BODY()
	
public:
	AL1Character(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
