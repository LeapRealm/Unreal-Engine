#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Util.generated.h"

class USceneManager;

UCLASS()
class FRAMEWORK_API UUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Manager")
	static USceneManager* GetSceneManager();
};
