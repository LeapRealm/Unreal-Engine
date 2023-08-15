#include "System/SkillComponent.h"

#include "SkillBase.h"
#include "Manager/DataManager.h"
#include "Util/Define.h"
#include "Util/Util.h"

USkillComponent::USkillComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

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

	USkillBase* SkillBase = NewObject<USkillBase>(SkillClass);
	if (SkillBase == nullptr)
	{
		LOG_ERROR(TEXT("Can't Create Skill Class"));
		return;
	}

	Skills.Add(SkillTag, SkillBase);
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

bool USkillComponent::Execute(const FGameplayTag& SkillTag)
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
	
	return (*Skills.Find(SkillTag))->Execute();
}
