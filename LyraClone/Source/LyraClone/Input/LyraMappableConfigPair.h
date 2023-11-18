#pragma once

#include "LyraMappableConfigPair.generated.h"

class UPlayerMappableInputConfig;

USTRUCT()
struct FLyraMappableConfigPair
{
	GENERATED_BODY()
	
public:
	FLyraMappableConfigPair() = default;

public:
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UPlayerMappableInputConfig> Config;

	UPROPERTY(EditAnywhere)
	bool bShouldActiveAutomatically = true;
};
