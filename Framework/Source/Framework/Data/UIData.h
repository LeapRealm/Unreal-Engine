#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "UIData.generated.h"

class UUI_Base;

UCLASS()
class FRAMEWORK_API UUIData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UClass* FindUIClassForTag(const FGameplayTag& UITag);
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, TSoftClassPtr<UUI_Base>> UIClasses;
};
