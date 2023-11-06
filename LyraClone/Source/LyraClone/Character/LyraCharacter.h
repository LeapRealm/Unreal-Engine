#pragma once

#include "GameFramework/Character.h"
#include "LyraCharacter.generated.h"

class ULyraPawnExtensionComponent;

UCLASS()
class ALyraCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	ALyraCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Lyra|Character")
	TObjectPtr<ULyraPawnExtensionComponent> PawnExtensionComponent;
};
