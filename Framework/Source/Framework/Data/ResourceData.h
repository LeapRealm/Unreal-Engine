#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ResourceData.generated.h"

UCLASS()
class FRAMEWORK_API UResourceData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	FSoftObjectPath FindResourcePathForTag(const FGameplayTag& ResourceTag);
	UClass* FindActorClassForTag(const FGameplayTag& ActorTag);
	UClass* FindWidgetClassForTag(const FGameplayTag& WidgetTag);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, TSoftObjectPtr<UObject>> ResourcePaths;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, TSoftClassPtr<AActor>> ActorClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, TSoftClassPtr<UUserWidget>> WidgetClasses;
};
