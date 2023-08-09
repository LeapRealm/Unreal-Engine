#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Managers.generated.h"

class UActorData;
class UResourceData;
class UUIData;
class UActorManager;
class UDataManager;
class UResourceManager;
class USceneManager;
class UUIManager;

UCLASS()
class FRAMEWORK_API UManagers : public UGameInstance, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UManagers();
	
	virtual void Init() override; 
	virtual void Tick(float DeltaTime) override;
	
public:
	FORCEINLINE UActorManager* GetActorManager() const { return ActorManager; }
	FORCEINLINE UDataManager* GetDataManager() const { return DataManager; }
	FORCEINLINE UResourceManager* GetResourceManager() const { return ResourceManager; }
	FORCEINLINE USceneManager* GetSceneManager() const { return SceneManager; }
	FORCEINLINE UUIManager* GetUIManager() const { return UIManager; }
	
	FORCEINLINE virtual TStatId GetStatId() const override { return Super::GetStatID(); }
	FORCEINLINE virtual UWorld* GetTickableGameObjectWorld() const override { return GetWorld(); }
	FORCEINLINE virtual ETickableTickType GetTickableTickType() const override { return IsTemplate() ? ETickableTickType::Never : FTickableGameObject::GetTickableTickType(); }
	FORCEINLINE virtual bool IsAllowedToTick() const override { return IsTemplate() == false; }

private:
	UPROPERTY(BlueprintReadOnly, Category="Manager", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UActorManager> ActorManager;

	UPROPERTY(BlueprintReadOnly, Category="Manager", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UDataManager> DataManager;
	
	UPROPERTY(BlueprintReadOnly, Category="Manager", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UResourceManager> ResourceManager;
	
	UPROPERTY(BlueprintReadOnly, Category="Manager", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneManager> SceneManager;

	UPROPERTY(BlueprintReadOnly, Category="Manager", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UUIManager> UIManager;
};
