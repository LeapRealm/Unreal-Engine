#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VoxelCharacter.generated.h"

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
	
	void CheckTeleportPlayerToCenter();
	void StartAttack();
	void StopAttack();
	bool AttackLineTrace(FIntVector& ChunkIndex3D, FIntVector& BlockIndex3D);
	void Interaction();

public:
	UPROPERTY(EditAnywhere)
	float LineTraceHitRange = 500.f;

private:
	FTimerHandle AttackTimerHandle;
	
private:
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

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AVoxelGameMode> VoxelGameMode;
};
