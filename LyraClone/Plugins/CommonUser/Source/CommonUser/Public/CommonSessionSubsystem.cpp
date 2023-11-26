#include "CommonSessionSubsystem.h"

#include "Engine/AssetManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CommonSessionSubsystem)

FString UCommonSession_HostSessionRequest::GetMapName() const
{
	FAssetData MapAssetData;
	if (UAssetManager::Get().GetPrimaryAssetData(MapID, MapAssetData))
	{
		return MapAssetData.PackageName.ToString();
	}
	return FString();
}

FString UCommonSession_HostSessionRequest::ConstructTravelURL() const
{
	FString CombinedExtraArgs;

	for (const auto& ExtraArg : ExtraArgs)
	{
		if (ExtraArg.Key.IsEmpty())
			continue;

		// ?를 구분자로 하는 복수개의 ExtraArg를 하나로 이어줍니다.
		// Value 값이 있을 경우에는 =를 이용해서 Key와 Value를 이어줍니다.
		if (ExtraArg.Value.IsEmpty())
		{
			CombinedExtraArgs += FString::Printf(TEXT("?%s"), *ExtraArg.Key);
		}
		else
		{
			CombinedExtraArgs += FString::Printf(TEXT("?%s=%s"), *ExtraArg.Key, *ExtraArg.Value);
		}
	}

	// 맵의 이름을 URL 맨 앞에 추가해서 최종 Travel URL을 만듭니다.
	return FString::Printf(TEXT("%s%s"), *GetMapName(), *CombinedExtraArgs);
}

UCommonSessionSubsystem::UCommonSessionSubsystem()
{
    
}

void UCommonSessionSubsystem::HostSession(APlayerController* HostingPlayer, UCommonSession_HostSessionRequest* Request)
{
	ULocalPlayer* LocalPlayer = (HostingPlayer != nullptr) ? HostingPlayer->GetLocalPlayer() : nullptr;
	if (LocalPlayer == nullptr)
		return;

	// HostSessionRequest에서 MapID와 ExtraArgs를 통해 URL을 생성해서 Map 로딩을 시작합니다.
	GetWorld()->ServerTravel(Request->ConstructTravelURL());
}
