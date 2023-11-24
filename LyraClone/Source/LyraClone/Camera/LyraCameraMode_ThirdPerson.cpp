#include "LyraCameraMode_ThirdPerson.h"

#include "Curves/CurveVector.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraCameraMode_ThirdPerson)

ULyraCameraMode_ThirdPerson::ULyraCameraMode_ThirdPerson(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void ULyraCameraMode_ThirdPerson::UpdateView(float DeltaTime)
{
	// CameraMode의 Owner는 CameraComponent입니다.
	// CameraComponent의 Owner인 Character(Pawn)을 활용해서 Pivot[Location|Rotation]을 반환합니다.
	FVector PivotLocation = GetPivotLocation();  // Character의 Location
	FRotator PivotRotation = GetPivotRotation(); // Character의 ControlRotation

	// Pitch 값에 대해 Min/Max로 Clamp 시킵니다.
	PivotRotation.Pitch = FMath::ClampAngle(PivotRotation.Pitch, ViewPitchMin, ViewPitchMax);

	// FLyraCameraModeView에 Pivot[Location|Rotation]을 설정합니다.
	View.Location = PivotLocation;
	View.Rotation = PivotRotation;

	// PivotRotation을 똑같이 ControlRotation으로 활용합니다.
	View.ControlRotation = View.Rotation;
	
	View.FieldOfView = FieldOfView;

	// Curve 데이터를 이용해서 카메라의 위치를 설정합니다.
	if (TargetOffsetCurve)
	{
		const FVector TargetOffset = TargetOffsetCurve->GetVectorValue(PivotRotation.Pitch);
		View.Location = PivotLocation + PivotRotation.RotateVector(TargetOffset);
	}
}
