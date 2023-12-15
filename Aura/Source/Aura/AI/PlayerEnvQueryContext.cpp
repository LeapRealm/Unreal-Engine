#include "PlayerEnvQueryContext.h"

#include "Character/AuraCharacter.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Kismet/GameplayStatics.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(PlayerEnvQueryContext)

UPlayerEnvQueryContext::UPlayerEnvQueryContext(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void UPlayerEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);
	
	TArray<AActor*> ActorSet;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAuraCharacter::StaticClass(), ActorSet);
	ActorSet.Remove(nullptr);
	if (ActorSet.Num())
	{
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, ActorSet);
	}
}
