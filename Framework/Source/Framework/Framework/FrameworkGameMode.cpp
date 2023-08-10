#include "FrameworkGameMode.h"

#include "Actor/TestActor.h"
#include "Manager/ActorManager.h"
#include "Manager/ResourceManager.h"
#include "Manager/WidgetManager.h"
#include "Widget/Popup/Widget_PopupBase.h"
#include "Util/Tag.h"
#include "Util/Util.h"

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
	{
		UUtil::GetUIManager(this)->ShowPopupUI<UWidget_PopupBase>(Tag::Asset_UI_TestPopup);
	}
	for (int32 i = 0; i < 5; i++)
	{
		UUtil::GetUIManager(this)->ClosePopupUI();
	}
}
