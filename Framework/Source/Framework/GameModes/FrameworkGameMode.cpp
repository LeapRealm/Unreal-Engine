#include "FrameworkGameMode.h"

#include "Actors/TestActor.h"
#include "Managers/ActorManager.h"
#include "Managers/ResourceManager.h"
#include "Utils/Tag.h"
#include "Utils/Util.h"

void AFrameworkGameMode::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle Handle;
	AFrameworkGameMode* Self = this;
	GetWorld()->GetTimerManager().SetTimer(Handle, [Self]()
	{
		ATestActor* TestActor1 = UUtil::GetActorManager(Self)->SpawnActor<ATestActor>(Tag::Asset_Native_TestActor, FVector(0, 0, 200.f));

		UUtil::GetResourceManager(Self)->LoadAsync(Tag::Asset_StaticMesh_WallDoor400x300, [TestActor1](UObject* Resource)
		{
			TestActor1->SkeletalMeshComponent->SetSkeletalMesh(Cast<USkeletalMesh>(Resource));
		});
	}, 3.f, false);
	
	// ATestActor* TestActor1 = UUtil::GetActorManager(this)->SpawnActor<ATestActor>(Tag::Asset_Native_TestActor, FVector(0, 0, 200.f));
	// ATestActor* TestActor2 = UUtil::GetActorManager(this)->SpawnActor<ATestActor>(Tag::Asset_Native_TestActor, FVector(0, 0, 800.f));
	
	// UUtil::GetResourceManager(this)->LoadAsync(Tag::Asset_StaticMesh_WallDoor400x300, [TestActor2](UObject* Resource)
	// {
	// 	TestActor2->SkeletalMeshComponent->SetSkeletalMesh(Cast<USkeletalMesh>(Resource));
	// });
}
