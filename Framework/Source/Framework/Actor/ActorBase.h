#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorBase.generated.h"

UCLASS()
class FRAMEWORK_API AActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AActorBase();

public:
	FORCEINLINE int64 GetInstanceID() const { return InstanceID; }
	FORCEINLINE void SetInstanceID(int64 InInstanceID) { InstanceID = InInstanceID; }

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	int64 InstanceID;
};
