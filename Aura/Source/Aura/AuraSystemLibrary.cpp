#include "AuraSystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Game/AuraGameMode.h"
#include "Kismet/GameplayStatics.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraSystemLibrary)

UAuraSystemLibrary::UAuraSystemLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void UAuraSystemLibrary::InitDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, UAbilitySystemComponent* ASC)
{
	if (AAuraGameMode* AuraGameMode = Cast<AAuraGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		AActor* AvatarActor = ASC->GetAvatarActor();
		UCharacterClassInfo* CharacterClassInfo = AuraGameMode->CharacterClassInfo;
		FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

		{
			FGameplayEffectContextHandle BaseAttributeContextHandle = ASC->MakeEffectContext();
			BaseAttributeContextHandle.AddSourceObject(AvatarActor);
			const FGameplayEffectSpecHandle BaseAttributeSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->BaseAttributes, 1.f, BaseAttributeContextHandle);
			ASC->ApplyGameplayEffectSpecToSelf(*BaseAttributeSpecHandle.Data.Get());
		}

		float Level = Cast<UAuraAttributeSet>(ASC->GetAttributeSet(UAuraAttributeSet::StaticClass()))->GetLevel();
		{
			FGameplayEffectContextHandle PrimaryAttributeContextHandle = ASC->MakeEffectContext();
			PrimaryAttributeContextHandle.AddSourceObject(AvatarActor);
			const FGameplayEffectSpecHandle PrimaryAttributeSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributeContextHandle);
			ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributeSpecHandle.Data.Get());
		}
		{
			FGameplayEffectContextHandle SecondaryAttributeContextHandle = ASC->MakeEffectContext();
			SecondaryAttributeContextHandle.AddSourceObject(AvatarActor);
			const FGameplayEffectSpecHandle SecondaryAttributeSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributeContextHandle);
			ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributeSpecHandle.Data.Get());
		}
		{
			FGameplayEffectContextHandle VitalAttributeContextHandle = ASC->MakeEffectContext();
			VitalAttributeContextHandle.AddSourceObject(AvatarActor);
			const FGameplayEffectSpecHandle VitalAttributeSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributeContextHandle);
			ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributeSpecHandle.Data.Get());
		}
	}
}
