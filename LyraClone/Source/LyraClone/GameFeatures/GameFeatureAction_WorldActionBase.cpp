#include "GameFeatureAction_WorldActionBase.h"

#include "GameFeaturesSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GameFeatureAction_WorldActionBase)

UGameFeatureAction_WorldActionBase::UGameFeatureAction_WorldActionBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void UGameFeatureAction_WorldActionBase::OnGameFeatureActivating(FGameFeatureActivatingContext& Context)
{
	for (const FWorldContext& WorldContext : GEngine->GetWorldContexts())
	{
		if (Context.ShouldApplyToWorldContext(WorldContext))
		{
			AddToWorld(WorldContext, Context);
		}
	}
}
