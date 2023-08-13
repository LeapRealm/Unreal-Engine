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

	ATestActor* TestActor1 = UUtil::GetActorManager(this)->SpawnActor<ATestActor>(Tag::Asset_Actor_TestActor, FVector(0, 0, 200.f));
	ATestActor* TestActor2 = UUtil::GetActorManager(this)->SpawnActor<ATestActor>(Tag::Asset_Actor_TestActor, FVector(0, 0, 400.f));
	
	UUtil::GetResourceManager(this)->LoadAsync<USkeletalMesh>(Tag::Asset_SkeletalMesh_Manny, [TestActor1](USkeletalMesh* Resource)
	{
		TestActor1->SkeletalMeshComponent->SetSkeletalMesh(Resource);
	});
	UUtil::GetResourceManager(this)->LoadAsync<USkeletalMesh>(Tag::Asset_SkeletalMesh_Manny, [TestActor2](USkeletalMesh* Resource)
	{
		TestActor2->SkeletalMeshComponent->SetSkeletalMesh(Resource);
	});

	for (int32 i = 0; i < 5; i++)
	{
		UUtil::GetWidgetManager(this)->ShowPopupWidget<UWidget_PopupBase>(Tag::Asset_Widget_TestPopup);
	}
	for (int32 i = 0; i < 5; i++)
	{
		UUtil::GetWidgetManager(this)->ClosePopupWidget();
	}
}
