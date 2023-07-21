#include "Controller/GASPlayerState.h"

#include "GASAbilitySystemComponent.h"
#include "GASAttributeSet.h"

AGASPlayerState::AGASPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UGASAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UGASAttributeSet>(TEXT("AttributeSet"));
}
