#pragma once
#include "ActiveGameplayEffectHandle.h"

#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
class USphereComponent;

UCLASS()
class AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:
	AAuraEffectActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditAnywhere, Category="Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, Category="Effect")
	bool bDestroyActorAfterEffectApplied = true;

	UPROPERTY(EditAnywhere, Category="Effect")
	bool bCancelEffectWhenEndOverlap = false;

	UPROPERTY(EditAnywhere, Category="Effect")
	float Level = 1.f;
	
	UPROPERTY()
	TMap<TObjectPtr<UAbilitySystemComponent>, FActiveGameplayEffectHandle> ActiveEffectHandles;
	
private:
	UPROPERTY(VisibleAnywhere, Category="Component")
	TObjectPtr<USceneComponent> SceneComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Component")
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere, Category="Component")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
};
