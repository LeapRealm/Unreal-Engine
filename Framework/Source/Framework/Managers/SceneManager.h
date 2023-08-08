#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SceneManager.generated.h"

UCLASS()
class FRAMEWORK_API USceneManager : public UObject
{
	GENERATED_BODY()

public:
	void ChangeScene(const FGameplayTag& SceneTag);

private:
	static FName TagToSceneName(const FGameplayTag& SceneTag);
};
