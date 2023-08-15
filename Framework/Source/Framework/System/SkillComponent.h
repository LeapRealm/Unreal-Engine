#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"

class USkillBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FRAMEWORK_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillComponent();

public:
	void AddSkill(const FGameplayTag& SkillTag);
	void RemoveSkill(const FGameplayTag& SkillTag);
	
	bool Execute(const FGameplayTag& SkillTag);
	
private:
	UPROPERTY(VisibleAnywhere)
	TMap<FGameplayTag, TObjectPtr<USkillBase>> Skills;
};
