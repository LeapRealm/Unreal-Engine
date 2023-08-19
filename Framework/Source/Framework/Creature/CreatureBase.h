#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "CreatureBase.generated.h"

struct FStatData;
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
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	virtual void OnDamage(const FGameplayTag& StatTag, const FStatData& StatData) { }
	
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
