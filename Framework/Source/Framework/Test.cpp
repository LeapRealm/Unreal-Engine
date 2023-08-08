#include "Test.h"

#include "Managers/ResourceManager.h"
#include "Utils/Tag.h"
#include "Utils/Util.h"

// Sets default values
ATest::ATest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATest::BeginPlay()
{
	Super::BeginPlay();

	AActor* Actor = UUtil::GetResourceManager(this)->SpawnActor(Tag::Asset_Blueprint_WallSconce, FVector(0, 0, 300.f));
	
	UUtil::GetResourceManager(this)->LoadAsync(Tag::Asset_StaticMesh_WallDoor400x300, [Actor](UObject* Resource)
	{
		Actor->FindComponentByClass<UStaticMeshComponent>()->SetStaticMesh(Cast<UStaticMesh>(Resource));
	});
}

// Called every frame
void ATest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

