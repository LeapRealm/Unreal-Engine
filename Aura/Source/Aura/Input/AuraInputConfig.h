#pragma once

#include "GameplayTagContainer.h"
#include "AuraInputConfig.generated.h"

class UInputAction;

UCLASS()
class UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UAuraInputConfig(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	const UInputAction* FindInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FGameplayTag, TObjectPtr<UInputAction>> TagToInputAction;
};
