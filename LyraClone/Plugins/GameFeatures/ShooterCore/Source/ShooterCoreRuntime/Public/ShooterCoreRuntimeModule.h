#pragma once

#include "CoreMinimal.h"

class FShooterCoreRuntimeModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
