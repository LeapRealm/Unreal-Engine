#include "AuraEffectActor.h"

#include "AbilitySystemGlobals.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraEffectActor)

AAuraEffectActor::AAuraEffectActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(SceneComponent);
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(GetRootComponent());
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	SphereComponent->SetupAttachment(GetRootComponent());
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);
}

void AAuraEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	check(InstantGameplayEffectClass);	
	
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OtherActor))
	{
		FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(InstantGameplayEffectClass, Level, EffectContextHandle);
		const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

		const bool bInfinite = (EffectSpecHandle.Data->Def->DurationPolicy == EGameplayEffectDurationType::Infinite);
		if (bInfinite && bCancelEffectWhenEndOverlap)
		{
			ActiveEffectHandles.Add(TargetASC, ActiveEffectHandle);
		}

		if (bDestroyActorAfterEffectApplied)
		{
			Destroy();
		}
	}
}

void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OtherActor))
	{
		FActiveGameplayEffectHandle* ActiveEffectHandle = ActiveEffectHandles.Find(TargetASC);
		if (ActiveEffectHandle)
		{
			TargetASC->RemoveActiveGameplayEffect(*ActiveEffectHandle, 1);
			ActiveEffectHandles.Remove(TargetASC);
		}
	}
}
