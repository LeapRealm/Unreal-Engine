#include "LyraPawnComponent_CharacterParts.h"

#include "GameplayTagAssetInterface.h"
#include "GameFramework/Character.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraPawnComponent_CharacterParts)

FLyraCharacterPartHandle FLyraCharacterPartList::AddEntry(const FLyraCharacterPart& NewPart)
{
	// PawnComponent의 CharacterPartList가 PartHandle을 관리하고, 이를 ControllerComponent_CharacterParts에 전달함
	FLyraCharacterPartHandle Result;
	Result.PartHandle = PartHandleCounter++;

	// Authority가 있다면, AppliedCharacterPartEntry를 Entries에 추가함
	if (ensure(OwnerComponent && OwnerComponent->GetOwner() && OwnerComponent->GetOwner()->HasAuthority()))
	{
		FLyraAppliedCharacterPartEntry& NewEntry = Entries.AddDefaulted_GetRef();
		NewEntry.Part = NewPart;
		NewEntry.PartHandle = Result.PartHandle;

		// 실제로 Actor를 생성하고, OwnerComponent의 OwnerActor에 Attach 시킴
		if (SpawnActorForEntry(NewEntry))
		{
			// BroadcastChanged를 통해, OwnerComponent에서 Owner의 SkeletalMeshComponent를 활용하여 Animation 및 Physics를 Re-Initialize 해줌
			OwnerComponent->BroadcastChanged();
		}
	}
	
	return Result;
}

void FLyraCharacterPartList::RemoveEntry(FLyraCharacterPartHandle Handle)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FLyraAppliedCharacterPartEntry& Entry = *EntryIt;

		// 제거할 경우에 PartHandle을 활용한다
		if (Entry.PartHandle == Handle.PartHandle)
		{
			DestroyActorForEntry(Entry);
		}
	}
}

bool FLyraCharacterPartList::SpawnActorForEntry(FLyraAppliedCharacterPartEntry& Entry)
{
	bool bCreatedAnyActor = false;

	// 전달된 AppliedCharacterPartEntry의 Part Class가 제대로 세팅되어 있다면
	if (Entry.Part.PartClass)
	{
		// OwnerComponent가 속한 World를 반환
		UWorld* World = OwnerComponent->GetWorld();

		// PawnComponent_CharacterParts의 어느 Component에 붙일 것인지 결정한다
		if (USceneComponent* ComponentToAttachTo = OwnerComponent->GetSceneComponentToAttachTo())
		{
			// 붙일 Component인 ComponentToAttachTo의 Bone 혹은 SocketName을 통해 어떻게 붙일지 Transform을 얻어온다
			const FTransform SpawnTransform = ComponentToAttachTo->GetSocketTransform(Entry.Part.SocketName);

			// Actor-Actor의 결합이므로, ChildActorComponent를 활용한다
			UChildActorComponent* PartComponent = NewObject<UChildActorComponent>(OwnerComponent->GetOwner());
			PartComponent->SetupAttachment(ComponentToAttachTo, Entry.Part.SocketName);
			PartComponent->SetChildActorClass(Entry.Part.PartClass);
			// RegisterComponent를 통해 RenderWorld인 FScene에 변경 내용을 전달 혹은 생성한다
			PartComponent->RegisterComponent();

			// ChildActorComponent에서 생성한 Actor를 반환하여
			if (AActor* SpawnedActor = PartComponent->GetChildActor())
			{
				// 새로 생성한 Actor의 Tick이 Parent Component의 Tick 이후에 실행되도록 선행조건을 붙인다
				if (USceneComponent* SpawnedRootComponent = SpawnedActor->GetRootComponent())
				{
					SpawnedRootComponent->AddTickPrerequisiteComponent(ComponentToAttachTo);
				}
			}
			Entry.SpawnedComponent = PartComponent;
			bCreatedAnyActor = true;
		}
	}

	return bCreatedAnyActor;
}

void FLyraCharacterPartList::DestroyActorForEntry(FLyraAppliedCharacterPartEntry& Entry)
{
	if (Entry.SpawnedComponent)
	{
		Entry.SpawnedComponent->DestroyComponent();
		Entry.SpawnedComponent = nullptr;
	}
}

FGameplayTagContainer FLyraCharacterPartList::CollectCombinedTags() const
{
	FGameplayTagContainer Result;

	// Entries를 순회하며
	for (const FLyraAppliedCharacterPartEntry& Entry : Entries)
	{
		// Part Actor가 생성되어 SpawnedComponent에 캐싱되어 있으면
		if (Entry.SpawnedComponent)
		{
			// 해당 Actor의 IGameplayTagAssetInterface를 통해 GameplayTag를 검색한다
			// - 현재 우리의 TaggedActor는 IGameplayTagAssetInterface를 상속받지 않으므로 그냥 넘어갈 것이다
			// - 만약에 각 Part에 대해 GameplayTag를 넣고 싶다면 Interface를 상속받아 정의해야 한다
			// - 예를 들어, Lv100이상만 장착 가능한 장비를 만들고 싶다면 넣어햐한다
			if (IGameplayTagAssetInterface* TagInterface = Cast<IGameplayTagAssetInterface>(Entry.SpawnedComponent->GetChildActor()))
			{
				TagInterface->GetOwnedGameplayTags(Result);
			}
		}
	}
	return Result;
}

ULyraPawnComponent_CharacterParts::ULyraPawnComponent_CharacterParts(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, CharacterPartList(this)
{
    
}

FLyraCharacterPartHandle ULyraPawnComponent_CharacterParts::AddCharacterPart(const FLyraCharacterPart& NewPart)
{
	return CharacterPartList.AddEntry(NewPart);
}

void ULyraPawnComponent_CharacterParts::RemoveCharacterPart(FLyraCharacterPartHandle Handle)
{
	CharacterPartList.RemoveEntry(Handle);
}

USceneComponent* ULyraPawnComponent_CharacterParts::GetSceneComponentToAttachTo() const
{
	// Parent에 SkeletalMeshComponent가 있으면 반환한다
	if (USkeletalMeshComponent* MeshComponent = GetParentMeshComponent())
	{
		return MeshComponent;
	}
	// OwnerActor가 존재하면 RootComponent를 반환한다
	else if (AActor* OwnerActor = GetOwner())
	{
		return OwnerActor->GetRootComponent();
	}
	// 이도저도 아니면 nullptr을 반환한다
	return nullptr;
}

USkeletalMeshComponent* ULyraPawnComponent_CharacterParts::GetParentMeshComponent() const
{
	// Character라면 기본적으로 제공하는 SkeletalMeshComponent를 반환한다
	if (AActor* OwnerActor = GetOwner())
	{
		if (ACharacter* OwningCharacter = Cast<ACharacter>(OwnerActor))
		{
			if (USkeletalMeshComponent* MeshComponent = OwningCharacter->GetMesh())
			{
				return MeshComponent;
			}
		}
	}
	return nullptr;
}

void ULyraPawnComponent_CharacterParts::BroadcastChanged()
{
	const bool bReInitPos = true;

	// 현재 Owner의 SkeletalMeshComponent를 반환한다
	if (USkeletalMeshComponent* MeshComponent = GetParentMeshComponent())
	{
		// BodyMeshes를 통해 GameplayTag를 활용하여 알맞은 SkeletalMesh로 재설정해준다
		const FGameplayTagContainer MergedTags = GetCombinedTags(FGameplayTag());
		USkeletalMesh* DesiredMesh = BodyMeshes.SelectBestBodyStyle(MergedTags);

		// SkeletalMesh와 Animation을 초기화 시켜준다
		MeshComponent->SetSkeletalMesh(DesiredMesh, bReInitPos);

		// PhysicsAsset을 초기화 시켜준다
		if (UPhysicsAsset* PhysicsAsset = BodyMeshes.ForcedPhysicsAsset)
		{
			MeshComponent->SetPhysicsAsset(PhysicsAsset, bReInitPos);
		}
	}
}

FGameplayTagContainer ULyraPawnComponent_CharacterParts::GetCombinedTags(FGameplayTag RequiredPrefix) const
{
	FGameplayTagContainer Result = CharacterPartList.CollectCombinedTags();
	if (RequiredPrefix.IsValid())
	{
		// 만약 GameplayTag를 통해 필터링할 경우에는 필터링해서 반환함
		return Result.Filter(FGameplayTagContainer(RequiredPrefix));
	}
	else
	{
		// 필터링할 GameplayTag가 없으면 그냥 반환함
		return Result;
	}
}
