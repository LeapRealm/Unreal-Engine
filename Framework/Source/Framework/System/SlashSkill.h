#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "System/SkillBase.h"
#include "Util/Tag.h"
#include "SlashSkill.generated.h"

UCLASS()
class FRAMEWORK_API USlashSkill : public USkillBase
{
	GENERATED_BODY()

public:
	USlashSkill();
	
public:
	virtual bool CanExecute() override;
	virtual bool TryExecute() override;
	virtual void Execute() override;

private:
	TArray<FGameplayTag> MontageTags = { Tag::Asset_Montage_SlashDown, Tag::Asset_Montage_SlashUp };
	int MontageTagIdx = 0;

	UPROPERTY(EditDefaultsOnly)
	int RequiredMana = 15.f;
};
