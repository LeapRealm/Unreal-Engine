#include "FrameworkGameMode.h"

#include "Actors/TestActor.h"
#include "Managers/ActorManager.h"
#include "Managers/ResourceManager.h"
#include "Managers/UIManager.h"
#include "UI/Popup/UI_PopupBase.h"
#include "Utils/Tag.h"
#include "Utils/Util.h"

void AFrameworkGameMode::BeginPlay()
{
	Super::BeginPlay();

	ATestActor* TestActor1 = UUtil::GetActorManager(this)->SpawnActor<ATestActor>(Tag::Asset_Native_TestActor, FVector(0, 0, 200.f));
	ATestActor* TestActor2 = UUtil::GetActorManager(this)->SpawnActor<ATestActor>(Tag::Asset_Native_TestActor, FVector(0, 0, 800.f));
	
	UUtil::GetResourceManager(this)->LoadAsync<UStaticMesh>(Tag::Asset_StaticMesh_Chair, [TestActor1](UStaticMesh* Resource)
	{
		TestActor1->StaticMeshComponent->SetStaticMesh(Resource);
	});
	UUtil::GetResourceManager(this)->LoadAsync<UStaticMesh>(Tag::Asset_StaticMesh_Chair, [TestActor2](UStaticMesh* Resource)
	{
		TestActor2->StaticMeshComponent->SetStaticMesh(Resource);
	});

	for (int32 i = 0; i < 5; i++)
		UUtil::GetUIManager(this)->ShowPopupUI<UUI_PopupBase>(Tag::Asset_UI_TestPopup);

	for (int32 i = 0; i < 5; i++)
		UUtil::GetUIManager(this)->ClosePopupUI();
}
