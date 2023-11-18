#include "LyraCameraMode_ThirdPerson.h"

#include "Curves/CurveVector.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraCameraMode_ThirdPerson)

ULyraCameraMode_ThirdPerson::ULyraCameraMode_ThirdPerson(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void ULyraCameraMode_ThirdPerson::UpdateView(float DeltaTime)
{
	Super::UpdateView(DeltaTime);

	// Curve 데이터를 이용해서 카메라의 위치를 설정합니다.
	if (TargetOffsetCurve)
	{
		const FVector TargetOffset = TargetOffsetCurve->GetVectorValue(GetPivotRotation().Pitch);
		View.Location = GetPivotLocation() + GetPivotRotation().RotateVector(TargetOffset);
	}
}
