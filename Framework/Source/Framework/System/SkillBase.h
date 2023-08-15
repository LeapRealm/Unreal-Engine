#pragma once

#include "CoreMinimal.h"
#include "SkillBase.generated.h"

UCLASS()
class FRAMEWORK_API USkillBase : public UObject
{
	GENERATED_BODY()

public:
	virtual bool Execute() { return false; }
};
