#include "Creature/GASMonster.h"

AGASMonster::AGASMonster()
{
}

void AGASMonster::BeginPlay()
{
	Super::BeginPlay();

	UnHighlightActor();
}

void AGASMonster::HighlightActor()
{
	bHighlighted = true;

	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
	
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(250);
}

void AGASMonster::UnHighlightActor()
{
	bHighlighted = false;

	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}
