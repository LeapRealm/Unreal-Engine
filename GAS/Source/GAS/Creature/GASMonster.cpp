#include "Creature/GASMonster.h"

#include "GASAbilitySystemComponent.h"
#include "GASAttributeSet.h"

AGASMonster::AGASMonster()
{
	AbilitySystemComponent = CreateDefaultSubobject<UGASAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UGASAttributeSet>(TEXT("AttributeSet"));
}

void AGASMonster::BeginPlay()
{
	Super::BeginPlay();

	UnHighlightActor();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
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
