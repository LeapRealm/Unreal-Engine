#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "WidgetData.generated.h"

class UWidget_Base;

UCLASS()
class FRAMEWORK_API UWidgetData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UClass* FindWidgetClassForTag(const FGameplayTag& UITag);
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, TSoftClassPtr<UWidget_Base>> WidgetClasses;
};
