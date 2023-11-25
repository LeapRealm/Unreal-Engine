#pragma once

#include "LyraCameraMode.generated.h"

class ULyraCameraComponent;

UENUM(BlueprintType)
enum class ELyraCameraModeBlendFunction : uint8
{
	Linear,
	EaseIn,
	EaseOut,
	EaseInOut,
	COUNT
};

struct FLyraCameraModeView
{
	FLyraCameraModeView();

	void Blend(const FLyraCameraModeView& Other, float OtherWeight);

	FVector Location;
	FRotator Rotation;
	FRotator ControlRotation;
	float FieldOfView;
};

UCLASS(Abstract, NotBlueprintable)
class ULyraCameraMode : public UObject
{
	GENERATED_BODY()

public:
	ULyraCameraMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void UpdateCameraMode(float DeltaTime);
	virtual void UpdateView(float DeltaTime);
	void UpdateBlending(float DeltaTime);
	
public:
	FVector GetPivotLocation() const;
	FRotator GetPivotRotation() const;
	AActor* GetTargetActor() const;
	ULyraCameraComponent* GetLyraCameraComponent() const;

public:
	FLyraCameraModeView View;

	UPROPERTY(EditDefaultsOnly, Category="View", meta=(UIMin="5.0", UIMax="170", ClampMin="5.0", ClampMax="170.0"))
	float FieldOfView;

	UPROPERTY(EditDefaultsOnly, Category="View", meta=(UIMin="-89.9", UIMax="89.9", ClampMin="-89.9", ClampMax="89.9"))
	float ViewPitchMin;

	UPROPERTY(EditDefaultsOnly, Category="View", meta=(UIMin="-89.9", UIMax="89.9", ClampMin="-89.9", ClampMax="89.9"))
	float ViewPitchMax;

	UPROPERTY(EditDefaultsOnly, Category="Blending")
	float BlendTime;
	
	float BlendAlpha;
	float BlendWeight;
	
	UPROPERTY(EditDefaultsOnly, Category="Blending")
	float BlendExponent;

	ELyraCameraModeBlendFunction BlendFunction;
};

UCLASS()
class ULyraCameraModeStack : public UObject
{
	GENERATED_BODY()
	
public:
	ULyraCameraModeStack(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void PushCameraMode(TSubclassOf<ULyraCameraMode>& CameraModeClass);
	void EvaluateStack(float DeltaTime, FLyraCameraModeView& OutCameraModeView);
	void UpdateStack(float DeltaTime);
	void BlendStack(FLyraCameraModeView& OutCameraModeView) const;
	
public:
	ULyraCameraMode* GetCameraModeInstance(TSubclassOf<ULyraCameraMode>& CameraModeClass);
	
public:
	UPROPERTY()
	TArray<TObjectPtr<ULyraCameraMode>> CameraModeInstances;
	
	UPROPERTY()
	TArray<TObjectPtr<ULyraCameraMode>> CameraModeStack;
};
