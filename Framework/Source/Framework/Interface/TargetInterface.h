#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TargetInterface.generated.h"

UINTERFACE(MinimalAPI)
class UTargetInterface : public UInterface
{
	GENERATED_BODY()
};

class FRAMEWORK_API ITargetInterface
{
	GENERATED_BODY()

public:
	virtual void HighlightActor() = 0;
	virtual void UnHighlightActor() = 0;
};
