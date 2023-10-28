#include "AuraEnemy.h"

#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraEnemy)

AAuraEnemy::AAuraEnemy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(52.f);
	GetCapsuleComponent()->SetCapsuleRadius(26.f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -48.f), FRotator(0.f, -90.f, 0.f));
}

void AAuraEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}
