#include "Actor/GASEffectActor.h"

#include "AbilitySystemInterface.h"
#include "GASAttributeSet.h"
#include "Components/SphereComponent.h"

AGASEffectActor::AGASEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
}

void AGASEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGASEffectActor::OnBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AGASEffectActor::OnEndOverlap);
}

void AGASEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UGASAttributeSet* GASAttributeSet = Cast<UGASAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UGASAttributeSet::StaticClass()));

		UGASAttributeSet* MutableGASAttributeSet = const_cast<UGASAttributeSet*>(GASAttributeSet);
		MutableGASAttributeSet->SetHealth(GASAttributeSet->GetHealth() + 25.f);
		MutableGASAttributeSet->SetMana(GASAttributeSet->GetMana() - 10.f);

		Destroy();
	}
}

void AGASEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	
}
