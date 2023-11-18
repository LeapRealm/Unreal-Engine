#pragma once

#include "LyraCameraMode.h"
#include "LyraCameraMode_ThirdPerson.generated.h"

class UCurveVector;

UCLASS(Abstract, Blueprintable)
class ULyraCameraMode_ThirdPerson : public ULyraCameraMode
{
	GENERATED_BODY()
	
public:
	ULyraCameraMode_ThirdPerson(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void UpdateView(float DeltaTime) override;

public:
	UPROPERTY(EditDefaultsOnly, Category="Third Person")
	TObjectPtr<const UCurveVector> TargetOffsetCurve;
};
