#pragma once

#include "CoreMinimal.h"
#include "Data/ResourceData.h"
#include "Engine/StreamableManager.h"
#include "ResourceManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FResourceLoadCompletedDelegate, UObject*);

UCLASS()
class FRAMEWORK_API UResourceManager : public UObject
{
	GENERATED_BODY()

public:
	void Init(UResourceData* InResourceData);
	
	void LoadAsync(const FGameplayTag& ResourceTag, TFunction<void(UObject*)> Callback, bool bAutoRelease = true);
	void Release(const FGameplayTag& ResourceTag);
	void Clear();
	
	AActor* SpawnActor(const FGameplayTag& ActorTag, const FVector& Location, const FRotator& Rotation = FRotator::ZeroRotator, const FVector& Scale = FVector::OneVector);
	void DestroyActor(AActor* Actor, float Seconds = 0.f);

private:
	FStreamableManager StreamableManager;
	
	TMap<FGameplayTag, TSharedPtr<FStreamableHandle>> TagToHandle;
	TMap<FGameplayTag, FResourceLoadCompletedDelegate> TagToDelegate;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UResourceData> ResourceData;
};

