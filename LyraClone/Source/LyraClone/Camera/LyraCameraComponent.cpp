#include "LyraCameraComponent.h"

#include "LyraCameraMode.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraCameraComponent)

ULyraCameraComponent::ULyraCameraComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, CameraModeStack(nullptr)
{
    
}

void ULyraCameraComponent::OnRegister()
{
	Super::OnRegister();

	if (CameraModeStack == nullptr)
	{
		CameraModeStack = NewObject<ULyraCameraModeStack>(this);
	}
}

void ULyraCameraComponent::GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView)
{
	check(CameraModeStack);

	// HeroComponent의 PawnData에서 DefaultCameraMode를 가져와서 CameraModeStack에 추가하고 CameraMode 블랜딩을 준비합니다.
	UpdateCameraModes();

	// EvaluateStack은 CameraModeStack에 있는 CameraMode들을 업데이트 및 블랜딩하고 CameraModeStack의 Bottom에서 Top까지 업데이트된 CameraMode들에 대해서 Lerp를 진행합니다.
	FLyraCameraModeView CameraModeView;
	CameraModeStack->EvaluateStack(DeltaTime, CameraModeView);

	if (APawn* TargetPawn = Cast<APawn>(GetTargetActor()))
	{
		if (APlayerController* PC = TargetPawn->GetController<APlayerController>())
		{
			// 해당 함수는 PC가 Possess하고 있는 Pawn의 RootComponent에 ControlRotation을 반영합니다.
			// 즉, 빙의중인 캐릭터를 회전시킵니다.
			PC->SetControlRotation(CameraModeView.ControlRotation);
		}
	}

	// 카메라의 Location과 Rotation을 반영합니다.
	SetWorldLocationAndRotation(CameraModeView.Location, CameraModeView.Rotation);

	// FOV 업데이트
	FieldOfView = CameraModeView.FieldOfView;

	// CameraModeView의 ControlRotation vs Rotation
	// ControlRotation: PC가 조종하는 Pawn의 Rotation에 적용할 값
	// Rotation: Camera에 반영하는 Rotation

	// FMinimalViewInfo를 업데이트 해줍니다.
	// - CameraComponent의 변화 사항을 최종 렌더링까지 반영하게 됩니다.
	DesiredView.Location = CameraModeView.Location;
	DesiredView.Rotation = CameraModeView.Rotation;
	DesiredView.FOV = CameraModeView.FieldOfView;
	DesiredView.OrthoWidth = OrthoWidth;
	DesiredView.OrthoNearClipPlane = OrthoNearClipPlane;
	DesiredView.OrthoFarClipPlane = OrthoFarClipPlane;
	DesiredView.AspectRatio = AspectRatio;
	DesiredView.bConstrainAspectRatio = bConstrainAspectRatio;
	DesiredView.bUseFieldOfViewForLOD = bUseFieldOfViewForLOD;
	DesiredView.ProjectionMode = ProjectionMode;
	DesiredView.PostProcessBlendWeight = PostProcessBlendWeight;
	if (PostProcessBlendWeight > 0.f)
	{
		DesiredView.PostProcessSettings = PostProcessSettings;
	}
}

void ULyraCameraComponent::UpdateCameraModes()
{
	check(CameraModeStack);

	if (DetermineCameraModeDelegate.IsBound())
	{
		if (TSubclassOf<ULyraCameraMode> CameraMode = DetermineCameraModeDelegate.Execute())
		{
			CameraModeStack->PushCameraMode(CameraMode);
		}
	}
}
