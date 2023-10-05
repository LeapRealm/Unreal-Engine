#include "CrackDecalBox.h"

#include "Define.h"

ACrackDecalBox::ACrackDecalBox()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	StaticMeshComponent->SetRelativeScale3D(FVector(1.01f));
	StaticMeshComponent->SetVisibility(false);
	SetRootComponent(StaticMeshComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Cube(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (SM_Cube.Succeeded())
		StaticMeshComponent->SetStaticMesh(SM_Cube.Object);
	
	static ConstructorHelpers::FObjectFinder<UMaterial> M_Block_Translucent(TEXT("/Script/Engine.Material'/Game/Materials/M_Block_Translucent.M_Block_Translucent'"));
	if (M_Block_Translucent.Succeeded())
		Material = M_Block_Translucent.Object;
}

void ACrackDecalBox::BeginPlay()
{
	Super::BeginPlay();
	
	MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(Material, this);
	StaticMeshComponent->SetMaterial(0, MaterialInstanceDynamic);
}

void ACrackDecalBox::SetVisibility(EBlockState BlockState)
{
	if (BlockState == EBlockState::NoCrack)
	{
		StaticMeshComponent->SetVisibility(false);
		return;
	}
	
	switch (BlockState)
	{
	case EBlockState::Crack1: MaterialInstanceDynamic->SetScalarParameterValue(TEXT("X"), 0); break;
	case EBlockState::Crack2: MaterialInstanceDynamic->SetScalarParameterValue(TEXT("X"), 2); break;
	case EBlockState::Crack3: MaterialInstanceDynamic->SetScalarParameterValue(TEXT("X"), 3); break;
	case EBlockState::Crack4: MaterialInstanceDynamic->SetScalarParameterValue(TEXT("X"), 5); break;
	}

	MaterialInstanceDynamic->SetScalarParameterValue(TEXT("Y"), 10.f);
	StaticMeshComponent->SetVisibility(true);
}
