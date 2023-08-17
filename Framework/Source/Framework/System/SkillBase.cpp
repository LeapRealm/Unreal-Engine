#include "System/SkillBase.h"

#include "StatComponent.h"
#include "Creature/PlayerBase.h"
#include "Util/Tag.h"

void USkillBase::Tick(float DeltaTime)
{
	if (LeftCoolTime == 0.f)
		return;
	
	LeftCoolTime = FMath::Max(LeftCoolTime - DeltaTime, 0.f);
}

bool USkillBase::CanExecute()
{
	if (Owner == nullptr)
		return false;
	
	if (LeftCoolTime > 0.f)
		return false;

	float Health = Owner->GetStatComponent()->GetValue(Tag::Stat_Health);
	if (Health <= 0.f)
		return false;
	
	return true;
}

bool USkillBase::TryExecute()
{
	if (CanExecute() == false)
		return false;

	LeftCoolTime = CoolTime;
	return true;
}

void USkillBase::Execute()
{
	LeftCoolTime = CoolTime;
}
