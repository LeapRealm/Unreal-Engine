#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Managers.generated.h"

class USceneManager;

UCLASS()
class FRAMEWORK_API UManagers : public UGameInstance, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UManagers();
	
	virtual void Init() override; 
	virtual void Tick(float DeltaTime) override;
	
public:
	FORCEINLINE USceneManager* GetSceneManager() { return SceneManager; }
	
	FORCEINLINE virtual TStatId GetStatId() const override { return Super::GetStatID(); }
	FORCEINLINE virtual UWorld* GetTickableGameObjectWorld() const override { return GetWorld(); }
	FORCEINLINE virtual ETickableTickType GetTickableTickType() const override { return IsTemplate() ? ETickableTickType::Never : FTickableGameObject::GetTickableTickType(); }
	FORCEINLINE virtual bool IsAllowedToTick() const override { return IsTemplate() == false; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Manager", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneManager> SceneManager;
};
