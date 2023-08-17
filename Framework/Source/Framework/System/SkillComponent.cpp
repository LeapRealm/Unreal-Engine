#include "System/SkillComponent.h"

#include "SkillBase.h"
#include "Creature/CreatureBase.h"
#include "Util/Define.h"

USkillComponent::USkillComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USkillComponent::RemoveSkill(const FGameplayTag& SkillTag)
{
	if (SkillTag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild Resource Tag"));
		return;
	}

	if (Skills.Contains(SkillTag) == false)
	{
		LOG_WARNING(TEXT("Can't find Skill"));
		return;
	}

	Skills.Remove(SkillTag);
}

bool USkillComponent::CanExecute(const FGameplayTag& SkillTag)
{
	if (SkillTag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild Resource Tag"));
		return false;
	}

	if (Skills.Contains(SkillTag) == false)
	{
		LOG_WARNING(TEXT("Can't Use Skill for SkillTag"));
		return false;
	}
	
	return (*Skills.Find(SkillTag))->CanExecute();
}

bool USkillComponent::TryExecute(const FGameplayTag& SkillTag)
{
	if (SkillTag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild Resource Tag"));
		return false;
	}

	if (Skills.Contains(SkillTag) == false)
	{
		LOG_WARNING(TEXT("Can't Use Skill for SkillTag"));
		return false;
	}
	
	return (*Skills.Find(SkillTag))->TryExecute();
}

void USkillComponent::Execute(const FGameplayTag& SkillTag)
{
	if (SkillTag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild Resource Tag"));
		return;
	}

	if (Skills.Contains(SkillTag) == false)
	{
		LOG_WARNING(TEXT("Can't Use Skill for SkillTag"));
		return;
	}
	
	(*Skills.Find(SkillTag))->Execute();
}
