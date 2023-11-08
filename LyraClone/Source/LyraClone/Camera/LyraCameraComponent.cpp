#include "LyraCameraComponent.h"

#include "LyraCameraMode.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraCameraComponent)

ULyraCameraComponent::ULyraCameraComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), CameraModeStack(nullptr)
{
    
}

void ULyraCameraComponent::OnRegister()
{
	Super::OnRegister();

	if (CameraModeStack == nullptr)
	{
		// BeginPlay와 같은 초기화가 딱히 필요없는 객체이기 때문에 NewObject로 할당합니다.
		CameraModeStack = NewObject<ULyraCameraModeStack>(this);
	}
}

void ULyraCameraComponent::GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView)
{
	check(CameraModeStack);

	UpdateCameraMode();
}

void ULyraCameraComponent::UpdateCameraMode()
{
	check(CameraModeStack);

	// DetermineCameraModeDelegate는 CameraMode Class를 반환합니다.
	// 해당 delegate에는 HeroComponent의 멤버 함수가 바인딩되어 있습니다.
	if (DetermineCameraModeDelegate.IsBound())
	{
		if (const TSubclassOf<ULyraCameraMode> CameraMode = DetermineCameraModeDelegate.Execute())
		{
			// CameraModeStack->PushCameraMode(CameraMode);
		}
	}
}
