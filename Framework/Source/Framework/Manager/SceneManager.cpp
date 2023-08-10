#include "SceneManager.h"

#include "WidgetManager.h"
#include "ActorManager.h"
#include "Kismet/GameplayStatics.h"
#include "Util/Util.h"

void USceneManager::ChangeScene(const FGameplayTag& SceneTag)
{
	UUtil::GetUIManager(this)->Clear();
	UUtil::GetActorManager(this)->Clear();
	
	UGameplayStatics::OpenLevel(GetWorld(), TagToSceneName(SceneTag));
}

FName USceneManager::TagToSceneName(const FGameplayTag& SceneTag)
{
	FString TagString = SceneTag.GetTagName().ToString();
	int32 LastDotPos = TagString.Find(TEXT("."), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	return FName(TagString.Mid(LastDotPos + 1));
}
