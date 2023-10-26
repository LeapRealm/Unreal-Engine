#pragma once
#include "GameFramework/Character.h"

#include "AuraCharacterBase.generated.h"

UCLASS()
class AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()
	
public:
	AAuraCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
