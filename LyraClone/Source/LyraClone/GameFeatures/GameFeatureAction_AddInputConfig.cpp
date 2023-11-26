#include "GameFeatureAction_AddInputConfig.h"

#include "EnhancedInputSubsystems.h"
#include "GameFeaturesSubsystem.h"
#include "Components/GameFrameworkComponentManager.h"
#include "LyraClone/Character/LyraHeroComponent.h"
#include "LyraClone/Input/LyraMappableConfigPair.h"
#include "PlayerMappableInputConfig.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GameFeatureAction_AddInputConfig)

UGameFeatureAction_AddInputConfig::UGameFeatureAction_AddInputConfig(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void UGameFeatureAction_AddInputConfig::OnGameFeatureActivating(FGameFeatureActivatingContext& Context)
{
	FPerContextData& ActiveData = ContextData.FindOrAdd(Context);
	if (ensure(ActiveData.ExtensionRequestHandles.IsEmpty()) == false ||
		ensure(ActiveData.PawnsAddedTo.IsEmpty()) == false)
	{
		Reset(ActiveData);
	}

	// 결국에는 자신의 AddToWorld()가 호출됩니다.
	Super::OnGameFeatureActivating(Context);
}

void UGameFeatureAction_AddInputConfig::OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context)
{
	Super::OnGameFeatureDeactivating(Context);

	FPerContextData* ActiveData = ContextData.Find(Context);
	if (ensure(ActiveData))
	{
		Reset(*ActiveData);
	}
}

void UGameFeatureAction_AddInputConfig::AddToWorld(const FWorldContext& WorldContext, const FGameFeatureStateChangeContext& ChangeContext)
{
	UWorld* World = WorldContext.World();
	UGameInstance* GameInstance = WorldContext.OwningGameInstance;
	FPerContextData& ActiveData = ContextData.FindOrAdd(ChangeContext);
	if (GameInstance && World && World->IsGameWorld())
	{
		if (UGameFrameworkComponentManager* ComponentManager = UGameInstance::GetSubsystem<UGameFrameworkComponentManager>(GameInstance))
		{
			// HandlePawnExtension 함수를 콜백 함수로 등록하기 위해서 델리게이트를 만듭니다.
			UGameFrameworkComponentManager::FExtensionHandlerDelegate AddConfigDelegate =
				UGameFrameworkComponentManager::FExtensionHandlerDelegate::CreateUObject(this, &ThisClass::HandlePawnExtension, ChangeContext);

			// GameFrameworkComponentManager를 이용해서 ExtensionHandler를 추가하여 델리게이트 등록을 진행합니다.
			TSharedPtr<FComponentRequestHandle> ExtensionRequestHandle = ComponentManager->AddExtensionHandler(APawn::StaticClass(), AddConfigDelegate);

			// 등록된 콜백 함수의 핸들을 ActiveData의 ExtensionRequestHandles에 추가합니다.
			ActiveData.ExtensionRequestHandles.Add(ExtensionRequestHandle);
		}
	}
}

void UGameFeatureAction_AddInputConfig::HandlePawnExtension(AActor* Actor, FName EventName, FGameFeatureStateChangeContext ChangeContext)
{
	APawn* AsPawn = CastChecked<APawn>(Actor);
	FPerContextData& ActiveData = ContextData.FindOrAdd(ChangeContext);

	if (EventName == UGameFrameworkComponentManager::NAME_ExtensionAdded || EventName == ULyraHeroComponent::NAME_BindInputsNow)
	{
		AddInputConfig(AsPawn, ActiveData);
	}
	else if (EventName == UGameFrameworkComponentManager::NAME_ExtensionRemoved || EventName == ULyraHeroComponent::NAME_BindInputsNow)
	{
		RemoveInputConfig(AsPawn, ActiveData);
	}
}

void UGameFeatureAction_AddInputConfig::AddInputConfig(APawn* Pawn, FPerContextData& ActiveData)
{
	APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());
	if (ULocalPlayer* LP = PlayerController ? PlayerController->GetLocalPlayer() : nullptr)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			FModifyContextOptions Options = {};
			Options.bIgnoreAllPressedKeysUntilRelease = false;

			// 추가된 InputConfig들을 순회하면서 EnhancedInputSubsystem에 PlayerMappableConfig를 추가합니다.
			for (const FLyraMappableConfigPair& Pair : InputConfigs)
			{
				if (Pair.bShouldActiveAutomatically)
				{
					Subsystem->AddPlayerMappableConfig(Pair.Config.LoadSynchronous(), Options);
				}
			}

			// ActiveData에 Pawn을 관리대상으로 등록합니다.
			ActiveData.PawnsAddedTo.AddUnique(Pawn);
		}
	}
}

void UGameFeatureAction_AddInputConfig::RemoveInputConfig(APawn* Pawn, FPerContextData& ActiveData)
{
	APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());
	if (ULocalPlayer* LP = PlayerController ? PlayerController->GetLocalPlayer() : nullptr)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			// InputConfig들을 순회하면서 EnhancedInputSubsystem에서 PlayerMappableConfig를 제거합니다.
			for (const FLyraMappableConfigPair& Pair : InputConfigs)
			{
				Subsystem->RemovePlayerMappableConfig(Pair.Config.LoadSynchronous());
			}

			// ActiveData에서 Pawn을 관리대상에서 뺍니다.
			ActiveData.PawnsAddedTo.Remove(Pawn);
		}
	}
}

void UGameFeatureAction_AddInputConfig::Reset(FPerContextData& ActiveData)
{
	// ExtensionRequestHandles 초기화
	ActiveData.ExtensionRequestHandles.Empty();

	// PawnsAddedTo를 하나씩 Stack 방식으로 위에서 아래로 순회하면서 InputConfig 제거를 진행합니다. 
	while (ActiveData.PawnsAddedTo.IsEmpty() == false)
	{
		TWeakObjectPtr<APawn> PawnPtr = ActiveData.PawnsAddedTo.Top();
		if (PawnPtr.IsValid())
		{
			RemoveInputConfig(PawnPtr.Get(), ActiveData);
		}
		else
		{
			// WeakObjectPtr로 PawnsAddedTo를 관리하고 있기 때문에 만약 GC가 되었다면 nullptr일 수 있습니다.
			// 그런 경우에는 그냥 Pop만 합니다.
			ActiveData.PawnsAddedTo.Pop();
		}
	}
}
