#pragma once

#include "EnvironmentQuery/EnvQueryContext.h"
#include "PlayerEnvQueryContext.generated.h"

UCLASS()
class UPlayerEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
	
public:
	UPlayerEnvQueryContext(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
};
