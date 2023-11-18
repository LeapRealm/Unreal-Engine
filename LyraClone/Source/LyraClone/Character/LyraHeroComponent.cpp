#include "LyraHeroComponent.h"

#include "EnhancedInputSubsystems.h"
#include "LyraPawnExtensionComponent.h"
#include "Components/GameFrameworkComponentManager.h"
#include "PlayerMappableInputConfig.h"
#include "LyraClone/LyraGameplayTags.h"
#include "LyraClone/Camera/LyraCameraComponent.h"
#include "LyraClone/Input/LyraInputComponent.h"
#include "LyraClone/Input/LyraMappableConfigPair.h"
#include "LyraClone/Player/LyraPlayerController.h"
#include "LyraClone/Player/LyraPlayerState.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraHeroComponent)

const FName ULyraHeroComponent::NAME_ActorFeatureName("Hero");

ULyraHeroComponent::ULyraHeroComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void ULyraHeroComponent::OnRegister()
{
	Super::OnRegister();

	// 올바른 Actor에 등록되었는지 확인합니다.
	if (GetPawn<APawn>() == nullptr)
	{
		return;
	}

	RegisterInitStateFeature();
}

void ULyraHeroComponent::BeginPlay()
{
	Super::BeginPlay();

	// PawnExtensionComponent를 관찰 대상으로 등록합니다.
	BindOnActorInitStateChanged(ULyraPawnExtensionComponent::NAME_ActorFeatureName, FGameplayTag(), false);

	// InitState_Spawned로 변경을 시도합니다.
	ensure(TryToChangeInitState(FLyraGameplayTags::Get().InitState_Spawned));

	// Force Update를 진행합니다.
	CheckDefaultInitialization();
}

void ULyraHeroComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterInitStateFeature();
	
	Super::EndPlay(EndPlayReason);
}

void ULyraHeroComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	if (Params.FeatureName == ULyraPawnExtensionComponent::NAME_ActorFeatureName)
	{
		// PawnExtensionComponent가 DataInitialized 상태로 변경되었을 경우, HeroComponent로 DataInitialized 상태로 변경합니다.
		const FLyraGameplayTags& InitTags = FLyraGameplayTags::Get();
		if (Params.FeatureState == InitTags.InitState_DataInitialized)
		{
			CheckDefaultInitialization();
		}
	}
}

bool ULyraHeroComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	APawn* Pawn = GetPawn<APawn>();
	const FLyraGameplayTags& InitTags = FLyraGameplayTags::Get();
	ALyraPlayerState* LyraPS = GetPlayerState<ALyraPlayerState>();

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
		// PlayerState가 없으면 변경 불가능
		if (LyraPS == nullptr)
		{
			return false;
		}

		return true;
	}

	// DataAvailable -> DataInitialized
	if (CurrentState == InitTags.InitState_DataAvailable && DesiredState == InitTags.InitState_DataInitialized)
	{
		// PawnExtensionComponent가 DataInitialized 될 때까지 기다립니다. (모든 Feature Component가 DataAvailable인 상태)
		return LyraPS && Manager->HasFeatureReachedInitState(Pawn, ULyraPawnExtensionComponent::NAME_ActorFeatureName, InitTags.InitState_DataInitialized);
	}

	// DataInitialized -> GameplayReady
	if (CurrentState == InitTags.InitState_DataInitialized && DesiredState == InitTags.InitState_GameplayReady)
	{
		return true;
	}
	
	// 이도저도 아니면 변경 불가능
	return false;
}

void ULyraHeroComponent::CheckDefaultInitialization()
{
	// Hero Feature는 Pawn Extension Feature에 종속되어 있으므로 CheckDefaultInitializationForImplementers를 호출하지 않습니다.
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

void ULyraHeroComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)
{
	const FLyraGameplayTags& InitTags = FLyraGameplayTags::Get();

	// DataAvailable -> DataInitialized 단계
	if (CurrentState == InitTags.InitState_DataAvailable && DesiredState == InitTags.InitState_DataInitialized)
	{
		APawn* Pawn = GetPawn<APawn>();
		ALyraPlayerState* LyraPS = GetPlayerState<ALyraPlayerState>();
		if (ensure(Pawn && LyraPS) == false)
		{
			return;
		}

		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
		const ULyraPawnData* PawnData = nullptr;
		if (ULyraPawnExtensionComponent* PawnExtensionComponent = ULyraPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
		{
			PawnData = PawnExtensionComponent->GetPawnData<ULyraPawnData>();
		}

		if (bIsLocallyControlled && PawnData)
		{
			// 현재 LyraCharacter에 Attach된 CameraComponent를 찾습니다.
			if (ULyraCameraComponent* CameraComponent = ULyraCameraComponent::FindCameraComponent(Pawn))
			{
				CameraComponent->DetermineCameraModeDelegate.BindUObject(this, &ThisClass::DetermineCameraMode);
			}
		}

		if (ALyraPlayerController* LyraPC = GetController<ALyraPlayerController>())
		{
			if (Pawn->InputComponent != nullptr)
			{
				InitializePlayerInput(Pawn->InputComponent);
			}
		}
	}
}

void ULyraHeroComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	const APawn* Pawn = GetPawn<APawn>();
	if (Pawn == nullptr)
		return;

	const APlayerController* PC = GetController<APlayerController>();
	check(PC);

	const ULocalPlayer* LP = PC->GetLocalPlayer();
	check(LP);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	// 모든 MappingContext를 비워줍니다.
	Subsystem->ClearAllMappings();

	// ULyraPawnExtensionComponent를 거쳐 ULyraPawnData에서 InputConfig를 가져옵니다.
	if (const ULyraPawnExtensionComponent* PawnExtensionComponent = ULyraPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (const ULyraPawnData* PawnData = PawnExtensionComponent->GetPawnData<ULyraPawnData>())
		{
			if (const ULyraInputConfig* InputConfig = PawnData->InputConfig)
			{
				const FLyraGameplayTags& GameplayTags = FLyraGameplayTags::Get();

				// HeroComponent가 가지고 있는 InputMappingContext들을 추가합니다.
				for (const FLyraMappableConfigPair& Pair : DefaultInputConfigs)
				{
					if (Pair.bShouldActiveAutomatically)
					{
						FModifyContextOptions Options = {};
						Options.bIgnoreAllPressedKeysUntilRelease = false;

						Subsystem->AddPlayerMappableConfig(Pair.Config.LoadSynchronous(), Options);
					}
				}

				// InputTag_Move(IA_Move)와 InputTag_Look_Mouse(IA_LookMouse)에 대해 각각 Input_Move()와 Input_LookMouse() 멤버 함수에 바인딩시킵니다.
				// 바인딩한 이후, Input 이벤트가 발생하면 해당되는 멤버 함수가 트리거됩니다.
				ULyraInputComponent* LyraIC = CastChecked<ULyraInputComponent>(PlayerInputComponent);
				LyraIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move, false);
				LyraIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ThisClass::Input_LookMouse, false);
			}
		}
	}
}

void ULyraHeroComponent::Input_Move(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();
	AController* Controller = Pawn ? Pawn->GetController() : nullptr;

	if (Controller)
	{
		const FVector2D Value = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

		if (Value.X != 0.f)
		{
			// World-Space기준으로 MovementRotation의 RightVector를 구합니다.
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			Pawn->AddMovementInput(MovementDirection, Value.X);
		}
		
		if (Value.Y != 0.f)
		{
			// World-Space기준으로 MovementRotation의 ForwardVector를 구합니다.
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			Pawn->AddMovementInput(MovementDirection, Value.Y);
		}
	}
}

void ULyraHeroComponent::Input_LookMouse(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();
	if (Pawn == nullptr)
		return;

	const FVector2D Value = InputActionValue.Get<FVector2D>();
	
	if (Value.X != 0.f)
	{
		// X에는 Yaw 값이 있습니다.
		// Camera의 Yaw값에 적용합니다.
		Pawn->AddControllerYawInput(Value.X);
	}

	if (Value.Y != 0.f)
	{
		// Y에는 Pitch 값이 있습니다.
		// Camera의 Pitch값에 적용합니다.
		Pawn->AddControllerPitchInput(-Value.Y);
	}
}

TSubclassOf<ULyraCameraMode> ULyraHeroComponent::DetermineCameraMode() const
{
	const APawn* Pawn = GetPawn<APawn>();
	if (Pawn == nullptr)
	{
		return nullptr;
	}

	if (ULyraPawnExtensionComponent* PawnExtensionComponent = ULyraPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (const ULyraPawnData* PawnData = PawnExtensionComponent->GetPawnData<ULyraPawnData>())
		{
			return PawnData->DefaultCameraMode;
		}
	}

	return nullptr;
}
