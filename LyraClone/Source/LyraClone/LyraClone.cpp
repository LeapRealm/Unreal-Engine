// Copyright Epic Games, Inc. All Rights Reserved.

#include "LyraClone.h"
#include "Modules/ModuleManager.h"

class FLyraGameModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FLyraGameModule::StartupModule()
{
	
}

void FLyraGameModule::ShutdownModule()
{
	
}

IMPLEMENT_PRIMARY_GAME_MODULE(FLyraGameModule, LyraClone, "LyraClone");
