#include "BlockingBox.h"

#include "Components/BoxComponent.h"

ABlockingBox::ABlockingBox()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetLineThickness(10.f);
	BoxComponent->SetCollisionProfileName(TEXT("BlockAll"));
	SetRootComponent(BoxComponent);
}

void ABlockingBox::SetBoxExtent(const FVector& BoxExtent)
{
	BoxComponent->SetBoxExtent(BoxExtent);
}
