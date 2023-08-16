#pragma once

#include "CoreMinimal.h"
#include "System/SkillBase.h"
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
};
