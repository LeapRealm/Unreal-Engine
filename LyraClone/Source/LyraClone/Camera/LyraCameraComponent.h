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
	void UpdateCameraMode();

public:
	static ULyraCameraComponent* FindCameraComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<ULyraCameraComponent>() : nullptr); }
	
public:
	// 카메라의 블랜딩 기능을 지원하는 스택
	UPROPERTY()
	TObjectPtr<ULyraCameraModeStack> CameraModeStack;

	// 현재 CameraMode를 가져오는 Delegate
	FLyraCameraModeDelegate DetermineCameraModeDelegate;
};
