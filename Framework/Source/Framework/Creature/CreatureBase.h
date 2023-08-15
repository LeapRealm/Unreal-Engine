#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "CreatureBase.generated.h"

class UStatComponent;
class USkillComponent;

UCLASS()
class FRAMEWORK_API ACreatureBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACreatureBase();

public:
	virtual void PostInitializeComponents() override;

public:
	FORCEINLINE FGameplayTag GetCreatureTag() const { return CreatureTag; }
	FORCEINLINE UStatComponent* GetStatComponent() const { return StatComponent; }
	FORCEINLINE USkillComponent* GetSkillComponent() const { return SkillComponent; }
	
protected:
	UPROPERTY(VisibleAnywhere)
	FGameplayTag CreatureTag;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStatComponent> StatComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkillComponent> SkillComponent;
};
