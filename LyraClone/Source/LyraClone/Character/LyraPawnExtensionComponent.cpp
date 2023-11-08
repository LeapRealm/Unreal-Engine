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
	if (Params.FeatureName != NAME_ActorFeatureName)
	{
		// PawnExtensionComponent는 다른 모든 Feature Component들의 상태가 DataAvailable일때 DataInitialized로 넘어갈 수 있습니다.
		// 여기서는 다른 Feature들이 DataAvailable로 변경될 때마다 지속적으로 CheckDefaultInitialization을 호출하여 DataInitialized로 상태 변경이 가능한지 확인합니다.
		const FLyraGameplayTags& InitTags = FLyraGameplayTags::Get();
		if (Params.FeatureState == InitTags.InitState_DataAvailable)
		{
			CheckDefaultInitialization();
		}
	}
}

bool ULyraPawnExtensionComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	APawn* Pawn = GetPawn<APawn>();
	const FLyraGameplayTags& InitTags = FLyraGameplayTags::Get();

	// InitState_Spawned로 초기화
	if (CurrentState.IsValid() == false && DesiredState == InitTags.InitState_Spawned)
	{
		// Pawn이 잘 세팅만 되어있으면 바로 Spawned로 넘어갑니다.
		if (Pawn)
		{
			return true;
		}
	}

	// Spawned -> DataAvailable
	if (CurrentState == InitTags.InitState_Spawned && DesiredState == InitTags.InitState_DataAvailable)
	{
		// PawnData가 없으면 변경 불가능
		if (PawnData == nullptr)
		{
			return false;
		}

		// LocallyControlled인 Pawn이 Controller가 없으면 변경 불가능
		const bool bHasAuthority = Pawn->HasAuthority();
		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
		if (bHasAuthority || bIsLocallyControlled)
		{
			if (GetController<AController>() == nullptr)
			{
				return false;
			}
		}

		return true;
	}

	// DataAvailable -> DataInitialized
	if (CurrentState == InitTags.InitState_DataAvailable && DesiredState == InitTags.InitState_DataInitialized)
	{
		// Actor에 바인드된 모든 Feature들이 DataAvailable 상태일 때 DataInitialized로 넘어감
		return Manager->HaveAllFeaturesReachedInitState(Pawn, InitTags.InitState_DataAvailable);
	}

	// DataInitialized -> GameplayReady
	if (CurrentState == InitTags.InitState_DataInitialized && DesiredState == InitTags.InitState_GameplayReady)
	{
		return true;
	}
	
	// 이도저도 아니면 변경 불가능
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

void ULyraPawnExtensionComponent::SetPawnData(const ULyraPawnData* InPawnData)
{
	// Pawn에 대해 Authority가 없을 경우에는 SetPawnData를 진행하지 않습니다.
	APawn* Pawn = GetPawnChecked<APawn>();
	if (Pawn->GetLocalRole() != ROLE_Authority)
	{
		return;
	}

	if (PawnData)
	{
		return;
	}

	PawnData = InPawnData;
}

void ULyraPawnExtensionComponent::SetupPlayerInputComponent()
{
	// ForceUpdate로 다시 InitState 상태 변환을 시작합니다. (연결 고리)
	CheckDefaultInitialization();
}
