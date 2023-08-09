#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Util.generated.h"

class UManagers;
class UActorManager;
class UDataManager;
class UResourceManager;
class USceneManager;
class UUIManager;

UCLASS()
class FRAMEWORK_API UUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Manager")
	static UManagers* GetManagers(UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category="Manager")
	static UActorManager* GetActorManager(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="Manager")
	static UDataManager* GetDataManager(UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category="Manager")
	static UResourceManager* GetResourceManager(UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category="Manager")
	static USceneManager* GetSceneManager(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="Manager")
	static UUIManager* GetUIManager(UObject* WorldContextObject);
};
