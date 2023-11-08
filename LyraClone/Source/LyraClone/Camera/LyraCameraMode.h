#pragma once

#include "LyraCameraMode.generated.h"

UCLASS(Abstract, NotBlueprintable)
class ULyraCameraMode : public UObject
{
	GENERATED_BODY()

public:
	ULyraCameraMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());	
};

UCLASS()
class ULyraCameraModeStack : public UObject
{
	GENERATED_BODY()
	
public:
	ULyraCameraModeStack(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	// 생성된 복수개의 CameraMode를 관리
	UPROPERTY()
	TArray<TObjectPtr<ULyraCameraMode>> CameraModeInstances;

	// Camera Matrix Blend 업데이트 진행 스택
	UPROPERTY()
	TArray<TObjectPtr<ULyraCameraMode>> CameraModeStack;
};
