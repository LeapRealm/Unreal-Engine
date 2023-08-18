#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Creature/CreatureBase.h"
#include "Manager/DataManager.h"
#include "Util/Define.h"
#include "Util/Util.h"
#include "SkillComponent.generated.h"

class USkillBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FRAMEWORK_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillComponent();

public:
	template <typename T>
	void AddSkill(const FGameplayTag& SkillTag);
	
	void RemoveSkill(const FGameplayTag& SkillTag);

	bool CanExecute(const FGameplayTag& SkillTag);
	void TryInfinite(const FGameplayTag& SkillTag);
	bool TryExecute(const FGameplayTag& SkillTag);
	void Execute(const FGameplayTag& SkillTag);

public:
	FORCEINLINE void SetAttacking(bool NewAttacking) { bAttacking = NewAttacking; }
	FORCEINLINE bool GetAttacking() const { return bAttacking; }
	
private:
	UPROPERTY(VisibleAnywhere)
	TMap<FGameplayTag, TObjectPtr<USkillBase>> Skills;

	UPROPERTY(VisibleAnywhere)
	bool bAttacking = false;
};

template <typename T>
void USkillComponent::AddSkill(const FGameplayTag& SkillTag)
{
	if (SkillTag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild Resource Tag"));
		return;
	}

	if (Skills.Contains(SkillTag))
	{
		LOG_WARNING(TEXT("This Skill has Already been Added"));
		return;
	}

	UClass* SkillClass = UUtil::GetDataManager(this)->FindObjectClassForTag(SkillTag);
	if (SkillClass == nullptr)
	{
		LOG_ERROR(TEXT("Can't Find Skill Class on Asset Data"));
		return;
	}

	T* SkillBase = NewObject<T>(SkillClass);
	if (SkillBase == nullptr)
	{
		LOG_ERROR(TEXT("Can't Create Skill Class"));
		return;
	}

	SkillBase->SetOwner(Cast<ACreatureBase>(GetOwner())); 
	Skills.Add(SkillTag, SkillBase);
}
