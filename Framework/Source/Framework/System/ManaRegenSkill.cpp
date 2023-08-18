#include "System/ManaRegenSkill.h"

#include "StatComponent.h"
#include "Creature/CreatureBase.h"
#include "Util/Tag.h"

UManaRegenSkill::UManaRegenSkill()
{
	LoopTime = 2.f;
}

bool UManaRegenSkill::CanExecute()
{
	if (Super::CanExecute() == false)
		return false;

	if (Owner->GetStatComponent()->GetValue(Tag::Stat_Mana) == Owner->GetStatComponent()->GetMaxValue(Tag::Stat_Mana))
		return false;
	
	return true;
}

bool UManaRegenSkill::TryExecute()
{
	if (Super::TryExecute() == false)
		return false;

	Execute();
	return true;
}

void UManaRegenSkill::Execute()
{
	Super::Execute();

	Owner->GetStatComponent()->AddValue(Tag::Stat_Mana, AddedMana);
}
