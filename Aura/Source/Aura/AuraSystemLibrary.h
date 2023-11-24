#pragma once

#include "Data/CharacterClassInfo.h"
#include "AuraSystemLibrary.generated.h"

class UAbilitySystemComponent;

UCLASS()
class UAuraSystemLibrary : public UBlueprintFunctionLibrary
{
 	GENERATED_BODY()
public:
	UAuraSystemLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UFUNCTION(BlueprintCallable)
 	static void InitDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable)
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC);
};
