#include "LyraUserFacingExperienceDefinition.h"

#include "CommonSessionSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraUserFacingExperienceDefinition)

ULyraUserFacingExperienceDefinition::ULyraUserFacingExperienceDefinition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

UCommonSession_HostSessionRequest* ULyraUserFacingExperienceDefinition::CreateHostingRequest() const
{
	const FString ExperienceName = ExperienceID.PrimaryAssetName.ToString();

	// HostSessionRequest는 UObject를 상속받고, UObject로 만든 객체는 GC의 대상이 되기 때문에 
	// UPROPERTY를 매크로를 사용해서 GC 당하지 않게 막는 작업이 수행되지 않는다면 다음 프레임에 GC 될수도 있습니다.
	// 하지만, 지금 만드는 객체는 현재 프레임에서만 사용하고 더 이상 사용하지 않으므로 GC에 대해 생각할 필요가 없습니다.
	UCommonSession_HostSessionRequest* Request = NewObject<UCommonSession_HostSessionRequest>();
	Request->MapID = MapID;
	Request->ExtraArgs.Add(TEXT("Experience"), ExperienceName);

	return Request;
}
