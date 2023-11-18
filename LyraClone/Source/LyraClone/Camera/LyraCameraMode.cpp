#include "LyraCameraMode.h"

#include "LyraCameraComponent.h"
#include "LyraPlayerCameraManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraCameraMode)

FLyraCameraModeView::FLyraCameraModeView()
	: Location(ForceInit)
	, Rotation(ForceInit)
	, ControlRotation(ForceInit)
	, FieldOfView(LYRA_CAMERA_DEFAULT_FOV)
{
	
}

void FLyraCameraModeView::Blend(const FLyraCameraModeView& Other, float OtherWeight)
{
	if (OtherWeight <= 0.f)
	{
		return;
	}
	else if (OtherWeight >= 1.f)
	{
		// OtherWeight가 1.0이면 Other를 덮어쓰면 됩니다.
		*this = Other;
		return;
	}

	// FMath::Lerp() -> Location + OtherWeight * (Other.Location - Location) 
	Location = FMath::Lerp(Location, Other.Location, OtherWeight);
	
	const FRotator DeltaRotation = (Other.Rotation - Rotation).GetNormalized();
	Rotation = Rotation + (OtherWeight * DeltaRotation);

	const FRotator DeltaControlRotation = (Other.ControlRotation - ControlRotation).GetNormalized();
	ControlRotation = ControlRotation + (OtherWeight * DeltaControlRotation);

	FieldOfView = FMath::Lerp(FieldOfView, Other.FieldOfView, OtherWeight);
}

ULyraCameraMode::ULyraCameraMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	FieldOfView = LYRA_CAMERA_DEFAULT_FOV;
	ViewPitchMin = LYRA_CAMERA_DEFAULT_PITCH_MIN;
	ViewPitchMax = LYRA_CAMERA_DEFAULT_PITCH_MAX;

	BlendTime = 0.f;
	BlendAlpha = 1.f;
	BlendWeight = 1.f;

	BlendFunction = ELyraCameraModeBlendFunction::EaseOut;
	BlendExponent = 4.f;
}

void ULyraCameraMode::UpdateCameraMode(float DeltaTime)
{
	// Actor를 활용해 Pivot[Location|Rotation]을 계산해서 View를 업데이트합니다.
	UpdateView(DeltaTime);

	// BlendWeight를 DeltaTime을 활용해 BlendAlpha를 계산한 후, BlendFunction에 맞게 재매핑하여 최종적으로 계산합니다.
	UpdateBlending(DeltaTime);
}

void ULyraCameraMode::UpdateView(float DeltaTime)
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
}

void ULyraCameraMode::UpdateBlending(float DeltaTime)
{
	// BlendAlpha를 DeltaTime을 이용해서 계산합니다.
	if (BlendTime > 0.f)
	{
		// BlendTime은 Blending 과정 총 시간(초)
		// BlendAlpha는 0에서 1로 변화하는 과정
		BlendAlpha += (DeltaTime / BlendTime);
	}
	else
	{
		BlendAlpha = 1.f;
	}

	// BlendAlpha[0~1]을 BlendFunction에 맞게 재매핑해서 BlendWeight[0~1]에 저장합니다.
	const float Exponent = (BlendExponent > 0.f) ? BlendExponent : 1.f;
	switch (BlendFunction)
	{
	case ELyraCameraModeBlendFunction::Linear:
		BlendWeight = BlendAlpha;
		break;
	case ELyraCameraModeBlendFunction::EaseIn:
		BlendWeight = FMath::InterpEaseIn(0.f, 1.f, BlendAlpha, Exponent);
		break;
	case ELyraCameraModeBlendFunction::EaseOut:
		BlendWeight = FMath::InterpEaseOut(0.f, 1.f, BlendAlpha, Exponent);
		break;
	case ELyraCameraModeBlendFunction::EaseInOut:
		BlendWeight = FMath::InterpEaseInOut(0.f, 1.f, BlendAlpha, Exponent);
		break;
	default:
		checkf(false, TEXT("UpdateBlending: Invalid BlendFunction [%d]\n"), (uint8)BlendFunction);
		break;
	}
}

FVector ULyraCameraMode::GetPivotLocation() const
{
	const AActor* TargetActor = GetTargetActor();
	check(TargetActor);

	if (const APawn* TargetPawn = Cast<APawn>(TargetActor))
	{
		// BaseEyeHeight를 고려하여 ViewLocation을 반환합니다.
		return TargetPawn->GetPawnViewLocation();
	}

	return TargetActor->GetActorLocation();
}

FRotator ULyraCameraMode::GetPivotRotation() const
{
	const AActor* TargetActor = GetTargetActor();
	check(TargetActor);

	if (const APawn* TargetPawn = Cast<APawn>(TargetActor))
	{
		// Pawn의 경우에는 ControlRotation을 반환합니다.
		return TargetPawn->GetViewRotation();
	}

	return TargetActor->GetActorRotation();
}

AActor* ULyraCameraMode::GetTargetActor() const
{
	const ULyraCameraComponent* LyraCameraComponent = GetLyraCameraComponent();
	return LyraCameraComponent->GetTargetActor();
}

ULyraCameraComponent* ULyraCameraMode::GetLyraCameraComponent() const
{
	// ULyraCameraModeStack::GetCameraModeInstance()에서 ULyraCameraMode를 생성했습니다.
	// ULyraCameraMode를 생성할 때, Outer 인자 값을 ULyraCameraModeStack::GetOuter()의 반환 값인 ULyraCameraComponent로 지정했습니다.
	return CastChecked<ULyraCameraComponent>(GetOuter());
}

ULyraCameraModeStack::ULyraCameraModeStack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void ULyraCameraModeStack::PushCameraMode(TSubclassOf<ULyraCameraMode>& CameraModeClass)
{
	if (CameraModeClass == nullptr)
		return;

	ULyraCameraMode* CameraMode = GetCameraModeInstance(CameraModeClass);
	check(CameraMode);

	int32 StackSize = CameraModeStack.Num();
	if ((StackSize > 0) && CameraModeStack[0] == CameraMode)
	{
		// 가장 최근에 이미 같은 CameraMode가 추가되었으므로 그냥 리턴합니다.
		return;
	}

	// ExistingStackIndex는 CameraModeStack에서 CameraMode에 맞는 Index를 찾습니다.
	// ExistingStackContribution은 Top에서 Bottom으로 최종 BlendWeight 값을 찾기 위해 초기값을 1.0으로 설정합니다.
	int32 ExistingStackIndex = INDEX_NONE;
	float ExistingStackContribution = 1.f;
	
	/*
	 * BlendWeight    |    ExistingStackContribution      |    ExistingStackContribution (accumulated)
	 * 0.1f           |    (1.0f)   * 0.1f   = 0.1f       |    (1.0f - 0.1f)         = 0.9f
	 * 0.3f           |    (0.9f)   * 0.3f   = 0.27f      |    (1.0f - 0.3f) * 0.9f  = 0.63f
	 * 0.6f           |    (0.63f)  * 0.6f   = 0.378f     |    (1.0f - 0.6f) * 0.63f = 0.252f
	 * 1.0f           |    (0.252f) * 1.0f   = 0.252f     | 
	 *                |    => 0.1f + 0.27f + 0.378f + 0.252f = [1.0f]
	 */
	for (int32 StackIndex = 0; StackIndex < StackSize; StackIndex++)
	{
		if (CameraModeStack[StackIndex] == CameraMode)
		{
			ExistingStackIndex = StackIndex;

			// 찾기를 원했던 동일한 CameraMode를 찾았기 때문에, ExistingStackContribution(누적된 BlendWeight)와 BlendWeight를 곱하고, 루프를 빠져나옵니다.
			ExistingStackContribution *= CameraMode->BlendWeight;
			break;
		}
		else
		{
			// 찾기를 원했던 CameraMode가 아니기 때문에, InverseBlendWeight = (1.0 - BlendWeight)를 곱해서 값을 누적시킵니다.
			ExistingStackContribution *= (1.f - CameraModeStack[StackIndex]->BlendWeight);
		}
	}

	// 인자로 넘어온 CameraMode를 Top으로 반영하기 위해서 중간에 있었다면 제거해서 다시 Push해 줍니다.
	if (ExistingStackIndex != INDEX_NONE)
	{
		CameraModeStack.RemoveAt(ExistingStackIndex);
		StackSize--;
	}
	else
	{
		// 같은게 없었다면 Contribution은 0으로 세팅합니다.
		ExistingStackContribution = 0.f;		
	}

	// BlendTime이 0보다 크다는 것은 Blend를 진행해야함을 의미하므로, ExistingStackContribution을 적용합니다.
	// 따라서, Blend를 하지 않는다면, BlendWeight에 1.0을 넣어서 적용합니다.
	const bool bShouldBlend = ((CameraMode->BlendTime > 0.f) && (StackSize > 0));
	const float BlendWeight = (bShouldBlend ? ExistingStackContribution : 1.f);
	CameraMode->BlendWeight = BlendWeight;

	CameraModeStack.Insert(CameraMode, 0);

	// 마지막 BlendWeight 값은 항상 1.0이 되어야합니다.
	CameraModeStack.Last()->BlendWeight = 1.f;
}

void ULyraCameraModeStack::EvaluateStack(float DeltaTime, FLyraCameraModeView& OutCameraModeView)
{
	// Top -> Bottom [0 -> Num]까지 순차적으로 Stack에 있는 CameraMode를 업데이트합니다.
	UpdateStack(DeltaTime);

	// Bottom -> Top까지 CameraModeStack에 대해 Blending을 진행해서 CameraModeView에 누적합니다.
	BlendStack(OutCameraModeView);
}

void ULyraCameraModeStack::UpdateStack(float DeltaTime)
{
	const int32 StackSize = CameraModeStack.Num();
	if (StackSize <= 0)
		return;

	// CameraModeStack을 순회하면서 CameraMode를 업데이트합니다.
	int32 RemoveCount = 0;
	int32 RemoveIndex = INDEX_NONE;
	for (int32 StackIndex = 0; StackIndex < StackSize; StackIndex++)
	{
		ULyraCameraMode* CameraMode = CameraModeStack[StackIndex];
		check(CameraMode);

		CameraMode->UpdateCameraMode(DeltaTime);

		// 만약 하나라도 CameraMode의 BlendWeight가 1.0에 도달했다면, 그 이후의 CameraMode들을 제거합니다.
		if (CameraMode->BlendWeight >= 1.f)
		{
			RemoveIndex = (StackIndex + 1);
			RemoveCount = (StackSize - RemoveIndex);
			break;
		}
	}

	if (RemoveCount > 0)
	{
		CameraModeStack.RemoveAt(RemoveIndex, RemoveCount);
	}
}

void ULyraCameraModeStack::BlendStack(FLyraCameraModeView& OutCameraModeView) const
{
	const int32 StackSize = CameraModeStack.Num();
	if (StackSize <= 0)
		return;

	// Bottom -> Top 순서로 Blend를 진행합니다.
	const ULyraCameraMode* CameraMode = CameraModeStack[StackSize - 1];
	check(CameraMode);

	// 가장 아래(Bottom)은 BlendWeight가 1.0입니다.
	OutCameraModeView = CameraMode->View;

	// [StackSize - 1]은 적용했으므로, [StackSize - 2]부터 순회합니다.
	for (int32 StackIndex = (StackSize - 2); StackIndex >= 0; StackIndex--)
	{
		CameraMode = CameraModeStack[StackIndex];
		check(CameraMode);

		OutCameraModeView.Blend(CameraMode->View, CameraMode->BlendWeight);
	}
}

ULyraCameraMode* ULyraCameraModeStack::GetCameraModeInstance(TSubclassOf<ULyraCameraMode>& CameraModeClass)
{
	check(CameraModeClass);

	// CameraModeInstances에서 이미 생성이 되어있는지 확인한 후에 있다면 반환합니다.
	for (ULyraCameraMode* CameraMode : CameraModeInstances)
	{
		if ((CameraMode != nullptr) && (CameraMode->GetClass() == CameraModeClass))
		{
			return CameraMode;
		}
	}

	// 없다면 새로 생성해서 반환합니다.
	// GetOuter() == ULyraCameraComponent
	ULyraCameraMode* NewCameraMode = NewObject<ULyraCameraMode>(GetOuter(), CameraModeClass, NAME_None, RF_NoFlags);
	check(NewCameraMode);

	// CameraModeInstances는 각각의 CameraModeClass에 대응하는 인스턴스들을 관리하는 컨테이너라는 것을 알 수 있습니다.
	CameraModeInstances.Add(NewCameraMode);

	return NewCameraMode;
}
