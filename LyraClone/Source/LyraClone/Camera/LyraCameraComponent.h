#pragma once

#include "Camera/CameraComponent.h"
#include "LyraCameraComponent.generated.h"

class ULyraCameraMode;
class ULyraCameraModeStack;
template<class TClass> class TSubclassOf;

DECLARE_DELEGATE_RetVal(TSubclassOf<ULyraCameraMode>, FLyraCameraModeDelegate);

UCLASS()
class ULyraCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
	
public:
	ULyraCameraComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void OnRegister() override;
	virtual void GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView) override;

private:
	void UpdateCameraModes();

public:
	static ULyraCameraComponent* FindCameraComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<ULyraCameraComponent>() : nullptr); }
	AActor* GetTargetActor() const { return GetOwner(); }
	
public:
	UPROPERTY()
	TObjectPtr<ULyraCameraModeStack> CameraModeStack;
	
	FLyraCameraModeDelegate DetermineCameraModeDelegate;
};
