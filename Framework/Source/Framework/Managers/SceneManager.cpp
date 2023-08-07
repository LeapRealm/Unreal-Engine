#include "SceneManager.h"

#include "Kismet/GameplayStatics.h"

void USceneManager::ChangeScene(const FGameplayTag& SceneTag)
{
	UGameplayStatics::OpenLevel(GetWorld(), TagToSceneName(SceneTag));
}

FName USceneManager::TagToSceneName(const FGameplayTag& SceneTag)
{
	FString TagString = SceneTag.GetTagName().ToString();
	int32 LastDotPos = TagString.Find(TEXT("."), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	return FName(TagString.Mid(LastDotPos + 1));
}
