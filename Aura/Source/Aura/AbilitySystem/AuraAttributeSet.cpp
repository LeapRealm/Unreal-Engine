#include "AuraAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraAttributeSet)

UAuraAttributeSet::UAuraAttributeSet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(0.f);
	InitMaxMana(50.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Properties;
	SetEffectProperties(Data, Properties);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Health, OldValue);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHealth, OldValue);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Mana, OldValue);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxMana, OldValue);
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties OutProps) const
{
	OutProps.EffectContextHandle = Data.EffectSpec.GetContext();
	OutProps.SourceASC = OutProps.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(OutProps.SourceASC) && OutProps.SourceASC->AbilityActorInfo.IsValid() && OutProps.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		OutProps.SourceAvatarActor = OutProps.SourceASC->AbilityActorInfo->AvatarActor.Get();
		OutProps.SourceController = OutProps.SourceASC->AbilityActorInfo->PlayerController.Get();

		if (OutProps.SourceController == nullptr && OutProps.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(OutProps.SourceAvatarActor))
			{
				OutProps.SourceController = Pawn->GetController();
			}
		}

		if (OutProps.SourceController)
		{
			OutProps.SourceCharacter = Cast<ACharacter>(OutProps.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		OutProps.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		OutProps.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		OutProps.TargetCharacter = Cast<ACharacter>(OutProps.TargetAvatarActor);
		OutProps.TargetASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OutProps.TargetAvatarActor);
	}
}
