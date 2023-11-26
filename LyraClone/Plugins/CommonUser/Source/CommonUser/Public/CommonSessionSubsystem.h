#pragma once

#include "CommonSessionSubsystem.generated.h"

// LyraClone 모듈에서 사용되어야 하기 때문에 Module Export가 필요합니다.
// 따라서, COMMONUSER_API를 추가해서 DLL Export가 가능하도록 해줍니다.

UCLASS(BlueprintType)
class COMMONUSER_API UCommonSession_HostSessionRequest : public UObject
{
	GENERATED_BODY()

public:
	// MapID를 맵의 이름(Text)로 변환합니다.
	FString GetMapName() const;

	// ServerTravel을 할 때 사용할 최종 URL을 만듭니다.
	FString ConstructTravelURL() const;

public:
	UPROPERTY(BlueprintReadWrite, Category="Session")
	FPrimaryAssetId MapID;
	
	// 맵을 로딩할때 전달할 매개변수들 (ex. 적용할 Experience의 이름)
	UPROPERTY(BlueprintReadWrite, Category="Session")
	TMap<FString, FString> ExtraArgs;
};

UCLASS()
class COMMONUSER_API UCommonSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UCommonSessionSubsystem();

public:
	UFUNCTION(BlueprintCallable, Category="Session")
	void HostSession(APlayerController* HostingPlayer, UCommonSession_HostSessionRequest* Request);
	
public:
	// 맵의 경로
	FString PendingTravelURL;
};
