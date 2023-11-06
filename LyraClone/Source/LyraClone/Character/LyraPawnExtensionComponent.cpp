#include "LyraPawnExtensionComponent.h"

#include "Components/GameFrameworkComponentManager.h"
#include "LyraClone/LyraGameplayTags.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraPawnExtensionComponent)

const FName ULyraPawnExtensionComponent::NAME_ActorFeatureName("PawnExtension");

ULyraPawnExtensionComponent::ULyraPawnExtensionComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void ULyraPawnExtensionComponent::OnRegister()
{
	Super::OnRegister();
	
	if (GetPawn<APawn>() == nullptr)
	{
		return;
	}
	
	RegisterInitStateFeature();
}

void ULyraPawnExtensionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	BindOnActorInitStateChanged(NAME_None, FGameplayTag(), false);
	ensure(TryToChangeInitState(FLyraGameplayTags::Get().InitState_Spawned));
	CheckDefaultInitialization();
}

void ULyraPawnExtensionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterInitStateFeature();
	
	Super::EndPlay(EndPlayReason);
}

void ULyraPawnExtensionComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	
}

bool ULyraPawnExtensionComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	return false;
}

void ULyraPawnExtensionComponent::CheckDefaultInitialization()
{
	CheckDefaultInitializationForImplementers();

	const FLyraGameplayTags& InitTags = FLyraGameplayTags::Get();
	
	static const TArray<FGameplayTag> StateChain =
	{
		InitTags.InitState_Spawned,
		InitTags.InitState_DataAvailable,
		InitTags.InitState_DataInitialized,
		InitTags.InitState_GameplayReady,
	};
	
	ContinueInitStateChain(StateChain);
}
