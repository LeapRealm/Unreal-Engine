#pragma once

#include "CoreMinimal.h"
#include "SkillBase.generated.h"

class ACreatureBase;

UCLASS()
class FRAMEWORK_API USkillBase : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual bool CanExecute();
	virtual bool TryExecute();
	virtual void Execute();

public:
	FORCEINLINE void SetOwner(ACreatureBase* NewOwner) { Owner = NewOwner; }
	
	FORCEINLINE virtual TStatId GetStatId() const override { return Super::GetStatID(); }
	FORCEINLINE virtual UWorld* GetTickableGameObjectWorld() const override { return GetWorld(); }
	FORCEINLINE virtual ETickableTickType GetTickableTickType() const override { return IsTemplate() ? ETickableTickType::Never : FTickableGameObject::GetTickableTickType(); }
	FORCEINLINE virtual bool IsAllowedToTick() const override { return IsTemplate() == false; }
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ACreatureBase> Owner;
	
	float CoolTime = 0.f;
	float LeftCoolTime = 0.f;
};
