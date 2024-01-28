#include "Modules/ModuleManager.h"

class FL1GameModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FL1GameModule::StartupModule()
{
	
}

void FL1GameModule::ShutdownModule()
{
	
}

IMPLEMENT_PRIMARY_GAME_MODULE(FL1GameModule, L1Game, "L1Game");
