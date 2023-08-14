#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Managers.generated.h"

class UDataManager;
class UResourceManager;
class USceneManager;
class UWidgetManager;

UCLASS()
class FRAMEWORK_API UManagers : public UGameInstance, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UManagers();
	
	virtual void Init() override; 
	virtual void Tick(float DeltaTime) override;
	
public:
	UDataManager* GetDataManager() const { return DataManager; }
	UResourceManager* GetResourceManager() const { return ResourceManager; }
	USceneManager* GetSceneManager() const { return SceneManager; }
	UWidgetManager* GetWidgetManager() const { return WidgetManager; }
	
	virtual TStatId GetStatId() const override { return Super::GetStatID(); }
	virtual UWorld* GetTickableGameObjectWorld() const override { return GetWorld(); }
	virtual ETickableTickType GetTickableTickType() const override { return IsTemplate() ? ETickableTickType::Never : FTickableGameObject::GetTickableTickType(); }
	virtual bool IsAllowedToTick() const override { return IsTemplate() == false; }

private:
	UPROPERTY(BlueprintReadOnly, Category="Manager", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UDataManager> DataManager;
	
	UPROPERTY(BlueprintReadOnly, Category="Manager", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UResourceManager> ResourceManager;
	
	UPROPERTY(BlueprintReadOnly, Category="Manager", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneManager> SceneManager;

	UPROPERTY(BlueprintReadOnly, Category="Manager", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UWidgetManager> WidgetManager;
};
