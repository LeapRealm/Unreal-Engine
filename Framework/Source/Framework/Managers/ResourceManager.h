#pragma once

#include "CoreMinimal.h"
#include "Data/ResourceData.h"
#include "Engine/StreamableManager.h"
#include "Utils/Util.h"
#include "ResourceManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FResourceLoadCompletedDelegate, UObject*);

UCLASS()
class FRAMEWORK_API UResourceManager : public UObject
{
	GENERATED_BODY()

public:
	void LoadAsync(const FGameplayTag& ResourceTag, TFunction<void(UObject*)> Callback, bool bAutoRelease = true);
	void Release(const FGameplayTag& ResourceTag);
	void Clear();

private:
	FStreamableManager StreamableManager;
	
	TMap<FGameplayTag, TSharedPtr<FStreamableHandle>> TagToHandle;
	TMap<FGameplayTag, FResourceLoadCompletedDelegate> TagToDelegate;
};
