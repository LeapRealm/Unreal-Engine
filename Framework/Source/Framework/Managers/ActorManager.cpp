#include "Managers/ActorManager.h"

#include "Actors/ActorBase.h"

void UActorManager::DestroyActor(AActorBase* Actor, float Seconds)
{
	if (Seconds > 0.f)
	{
		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, [this, Actor]()
		{
			RemoveActor(Actor);
			GetWorld()->DestroyActor(Actor);
		}, Seconds, false);
	}
	else
	{
		RemoveActor(Actor);
		GetWorld()->DestroyActor(Actor);
	}
}

void UActorManager::Clear()
{
	for (const auto& Tuple : InstanceIDToActor)
		DestroyActor(Tuple.Value);
	InstanceIDToActor.Empty();
}

void UActorManager::AddActor(AActorBase* Actor)
{
	if (IsValid(Actor) == false)
		return;

	Actor->SetInstanceID(NextInstanceID++);
	InstanceIDToActor.Add(Actor->GetInstanceID(), Actor);
}

void UActorManager::RemoveActor(AActorBase* Actor)
{
	if (IsValid(Actor) == false)
		return;

	InstanceIDToActor.Remove(Actor->GetInstanceID());
}
