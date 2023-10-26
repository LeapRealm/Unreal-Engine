#pragma once

#include "LyraGameInstance.generated.h"

UCLASS()
class ULyraGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	ULyraGameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void Init() override;
	virtual void Shutdown() override;
};
