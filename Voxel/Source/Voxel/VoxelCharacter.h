#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "GameFramework/Character.h"
#include "VoxelCharacter.generated.h"

class USpringArmComponent;
class AVoxelGameMode;
class ACrackDecalBox;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class UCameraComponent;

UCLASS()
class VOXEL_API AVoxelCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AVoxelCharacter();

public:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	void StartAttack();
	void Attacking();
	void StopAttack();
	
	void TryCrackBlock();
	void TryPlaceBlock();

	void ToggleViewMode();

private:
	void CheckTeleportPlayerToCenter();
	bool LineTrace(FHitResult& OutHitResult);
	bool FindBlockAndCanCrackBlock(FIntVector& OutHitChunkIndex, FIntVector& OutHitBlockIndex);

public:
	UPROPERTY(EditAnywhere)
	float LineTraceHitRange = 500.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D LastMoveInputValue = FVector2D::ZeroVector;

private:
	float TargetAttackTime = 0.25f;
	float CurrentAttackTime = 0.f;
	EViewMode ViewMode = EViewMode::First;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ACrackDecalBox> CrackDecalBox;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> InteractionAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> ToggleViewModeAction;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AVoxelGameMode> VoxelGameMode;
};
