#pragma once

#include "LyraCameraMode.h"
#include "LyraCameraMode_ThirdPerson.generated.h"

UCLASS(Abstract, Blueprintable)
class ULyraCameraMode_ThirdPerson : public ULyraCameraMode
{
	GENERATED_BODY()
	
public:
	ULyraCameraMode_ThirdPerson(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
