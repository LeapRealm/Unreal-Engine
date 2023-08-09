#pragma once

#include "CoreMinimal.h"
#include "DataManager.h"
#include "GameplayTagContainer.h"
#include "Data/ActorData.h"
#include "Utils/Define.h"
#include "Utils/Util.h"
#include "ActorManager.generated.h"

class AActorBase;

UCLASS()
class FRAMEWORK_API UActorManager : public UObject
{
	GENERATED_BODY()

public:
	template<typename T>
	T* SpawnActor(const FGameplayTag& ActorTag, const FVector& Location, const FRotator& Rotation = FRotator::ZeroRotator, const FVector& Scale = FVector::OneVector);
	void DestroyActor(AActorBase* Actor, float Seconds = 0.f);
	void Clear();
	
private:
	void AddActor(AActorBase* Actor);
	void RemoveActor(AActorBase* Actor);
	
private:
	int64 NextInstanceID = 0;

	UPROPERTY(VisibleAnywhere)
	TMap<int64, TObjectPtr<AActorBase>> InstanceIDToActor;
};

template <typename T>
T* UActorManager::SpawnActor(const FGameplayTag& ActorTag, const FVector& Location, const FRotator& Rotation, const FVector& Scale)
{
	if (ActorTag.IsValid() == false)
	{
		LOG_ERROR(TEXT("Invaild Actor Tag"));
		return nullptr;
	}

	UActorData* ActorData = UUtil::GetDataManager(this)->GetActorData();
	UClass* ActorClass = ActorData->FindActorClassForTag(ActorTag);
	if (ActorClass == nullptr)
	{
		LOG_ERROR(TEXT("Can't Find Actor Class on Actor Data"));
		return nullptr;
	}

	FTransform Transform;
	Transform.SetLocation(Location);
	Transform.SetRotation(Rotation.Quaternion());
	Transform.SetScale3D(Scale);

	T* SpawnedActor = Cast<T>(GetWorld()->SpawnActor(ActorClass, &Transform, FActorSpawnParameters()));
	AddActor(SpawnedActor);
	return SpawnedActor;
}
