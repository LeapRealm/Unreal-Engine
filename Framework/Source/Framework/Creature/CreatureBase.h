#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CreatureBase.generated.h"

UCLASS()
class FRAMEWORK_API ACreatureBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACreatureBase();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
