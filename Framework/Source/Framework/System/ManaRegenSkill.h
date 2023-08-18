#pragma once

#include "CoreMinimal.h"
#include "System/SkillBase.h"
#include "ManaRegenSkill.generated.h"

UCLASS()
class FRAMEWORK_API UManaRegenSkill : public USkillBase
{
	GENERATED_BODY()

public:
	UManaRegenSkill();
	
public:
	virtual bool CanExecute() override;
	virtual bool TryExecute() override;
	virtual void Execute() override;

private:
	UPROPERTY(EditDefaultsOnly)
	int AddedMana = 10.f;
};
