#pragma once

#include "LyraCharacterPartTypes.h"
#include "LyraCosmeticAnimationTypes.h"
#include "Components/PawnComponent.h"
#include "LyraPawnComponent_CharacterParts.generated.h"

// 인스턴스화 된 Character Part의 단위
USTRUCT()
struct FLyraAppliedCharacterPartEntry
{
	GENERATED_BODY()

	// Character Part의 메타 데이터(클래스 정보)
	UPROPERTY()
	FLyraCharacterPart Part;

	// LyraCharacterPartList에서 할당 받은 Part 핸들값 (LyraControllerCharacterPartEntry의 Handle 값과 같으면 같은 Part로 인식함)
	UPROPERTY()
	int32 PartHandle = INDEX_NONE;

	// 인스턴스화 된 Character Part Actor를 가지고 있는 ChildActorComponent
	UPROPERTY()
	TObjectPtr<UChildActorComponent> SpawnedComponent = nullptr;
};

// LyraPawnComponent_CharacterParts에서 실질적으로 Character Part들을 관리하는 구조체
USTRUCT(BlueprintType)
struct FLyraCharacterPartList
{
	GENERATED_BODY()

	FLyraCharacterPartList()
		: OwnerComponent(nullptr) { }
	FLyraCharacterPartList(ULyraPawnComponent_CharacterParts* InOwnerComponent)
		: OwnerComponent(InOwnerComponent) { }

	FLyraCharacterPartHandle AddEntry(const FLyraCharacterPart& NewPart);
	void RemoveEntry(FLyraCharacterPartHandle Handle);
	
	bool SpawnActorForEntry(FLyraAppliedCharacterPartEntry& Entry);
	void DestroyActorForEntry(FLyraAppliedCharacterPartEntry& Entry);

	FGameplayTagContainer CollectCombinedTags() const;

	// 현재 인스턴스화된 Character Part들
	UPROPERTY()
	TArray<FLyraAppliedCharacterPartEntry> Entries;

	// 해당 LyraCharacterPartList의 Owner인 PawnComponent
	UPROPERTY()
	TObjectPtr<ULyraPawnComponent_CharacterParts> OwnerComponent;

	// PartHandle의 값을 할당 및 관리하는 변수
	int32 PartHandleCounter = 0;
};

// Character Part들을 인스턴스화하여 관리하는 PawnComponent
UCLASS(meta=(BlueprintSpawnableComponent))
class ULyraPawnComponent_CharacterParts : public UPawnComponent
{
	GENERATED_BODY()
	
public:
	ULyraPawnComponent_CharacterParts(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	FLyraCharacterPartHandle AddCharacterPart(const FLyraCharacterPart& NewPart);
	void RemoveCharacterPart(FLyraCharacterPartHandle Handle);
	
	USceneComponent* GetSceneComponentToAttachTo() const;
	USkeletalMeshComponent* GetParentMeshComponent() const;
	void BroadcastChanged();
	FGameplayTagContainer GetCombinedTags(FGameplayTag RequiredPrefix) const;

public:
	// 인스턴스화 된 Character Parts
	UPROPERTY()
	FLyraCharacterPartList CharacterPartList;

	// 애니메이션 적용을 위한 Mesh와의 연결고리
	UPROPERTY(EditAnywhere, Category="Cosmetics")
	FLyraAnimBodyStyleSelectionSet BodyMeshes;
};
