#include "AuraHealthBar.h"

#include "AbilitySystem/AuraAttributeSet.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraHealthBar)

UAuraHealthBar::UAuraHealthBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void UAuraHealthBar::BindDelegates()
{
	Super::BindDelegates();

	BIND_ATTRIBUTE_CHANGE_SEPARATE_FUNCTION(Health);
	BIND_ATTRIBUTE_CHANGE_SEPARATE_FUNCTION(MaxHealth);
}
