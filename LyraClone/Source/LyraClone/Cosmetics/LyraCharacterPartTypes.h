#pragma once

#include "LyraCharacterPartTypes.generated.h"

USTRUCT(BlueprintType)
struct FLyraCharacterPartHandle
{
	GENERATED_BODY()

	void Reset()
	{
		PartHandle = INDEX_NONE;
	}

	bool IsValid() const
	{
		return PartHandle != INDEX_NONE;
	}

	UPROPERTY()
	int32 PartHandle = INDEX_NONE;
};

USTRUCT(BlueprintType)
struct FLyraCharacterPart
{
	GENERATED_BODY()

	// Part Actor의 Class 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> PartClass;

	// Part Actor를 스폰하여 붙일떄 어떤 Bone에 붙일지에 대한 정보(따로 정의되어 있지 않다면 Root에 붙임) 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;
};
