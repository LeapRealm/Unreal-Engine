#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"

class USkillBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FRAMEWORK_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillComponent();

private:
	UPROPERTY()
	TArray<TObjectPtr<USkillBase>> Skills;
};
