#pragma once

#include "GameplayTagContainer.h"
#include "LyraCosmeticAnimationTypes.generated.h"

USTRUCT(BlueprintType)
struct FLyraAnimLayerSelectionEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> Layer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer RequiredTags;
};

USTRUCT(BlueprintType)
struct FLyraAnimLayerSelectionSet
{
	GENERATED_BODY()

	// AnimInstance의 Rule을 가진 LayerRules
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FLyraAnimLayerSelectionEntry> LayerRules;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> DefaultLayer;
};

USTRUCT(BlueprintType)
struct FLyraAnimBodyStyleSelectionEntry
{
	GENERATED_BODY()

	// AnimLayer를 적용할 SkeletalMesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMesh> Mesh = nullptr;

	// Cosmetic Tag라고 생각하면 됨 (해당 태그들을 가지고 있어야 착용이 가능함)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Cosmetic"))
	FGameplayTagContainer RequiredTags;
};

USTRUCT(BlueprintType)
struct FLyraAnimBodyStyleSelectionSet
{
	GENERATED_BODY()

	// GameplayTag를 통해 Mesh Rules에 따라 알맞은 BodyStyle을 반환한다
	USkeletalMesh* SelectBestBodyStyle(const FGameplayTagContainer& CosmeticTags) const;
	
	// AnimLayer를 적용할 SkeletalMesh를 들고 있음 (Animation과 Mesh간의 Rule을 MeshRules라고 생각하면 됨)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FLyraAnimBodyStyleSelectionEntry> MeshRules;

	// 디폴트로 적용할 SkeletalMesh (Fallback)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMesh> DefaultMesh = nullptr;

	// Physics Asset은 하나로 통일함 (즉, 모든 Animation의 Physics 속성은 서로 공유함)
	UPROPERTY(EditAnywhere)
	TObjectPtr<UPhysicsAsset> ForcedPhysicsAsset = nullptr;
};
