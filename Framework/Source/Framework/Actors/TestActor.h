#pragma once

#include "CoreMinimal.h"
#include "Actors/ActorBase.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

class USkeletalMeshComponent;

UCLASS()
class FRAMEWORK_API ATestActor : public AActorBase
{
	GENERATED_BODY()
	
public:	
	ATestActor();

public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
};
