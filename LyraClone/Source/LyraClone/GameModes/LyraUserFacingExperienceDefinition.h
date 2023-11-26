#pragma once

#include "LyraUserFacingExperienceDefinition.generated.h"

class UCommonSession_HostSessionRequest;

UCLASS(BlueprintType)
class ULyraUserFacingExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	ULyraUserFacingExperienceDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	// Map 로딩 및 Experience 전환을 위해서 MapID와 ExperienceID를 활용하여 HostSessionRequest를 만듭니다.
	UFUNCTION(BlueprintCallable, BlueprintPure=false)
	UCommonSession_HostSessionRequest* CreateHostingRequest() const;
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Experience, meta=(AllowedTypes="Map"))
	FPrimaryAssetId MapID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Experience, meta=(AllowedTypes="LyraExperienceDefinition"))
	FPrimaryAssetId ExperienceID;
};
