#pragma once

#include "CoreMinimal.h"
#include "DataManager.generated.h"

class UActorData;
class UResourceData;
class UUIData;

UCLASS()
class FRAMEWORK_API UDataManager : public UObject
{
	GENERATED_BODY()

public:
	UDataManager();

	FORCEINLINE UActorData* GetActorData() const { return ActorData; }
	FORCEINLINE UResourceData* GetResourceData() const { return ResourceData; }
	FORCEINLINE UUIData* GetUIData() const { return UIData; }
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UActorData> ActorData;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UResourceData> ResourceData;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UUIData> UIData;
};
