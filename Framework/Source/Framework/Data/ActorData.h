#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ActorData.generated.h"

class AActorBase;

UCLASS()
class FRAMEWORK_API UActorData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UClass* FindActorClassForTag(const FGameplayTag& ActorTag);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, TSoftClassPtr<AActorBase>> ActorClasses;
};
