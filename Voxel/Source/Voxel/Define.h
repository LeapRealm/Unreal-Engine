﻿#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "Define.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCustom, Log, All);

#define CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define LOG_CALLINFO(Verbosity) UE_LOG(LogCustom, Verbosity, TEXT("%s"), *CALLINFO)
#define LOG(Format, ...) UE_LOG(LogCustom, Display, TEXT("%s %s"), *CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define LOG_WARNING(Format, ...) UE_LOG(LogCustom, Warning, TEXT("%s %s"), *CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define LOG_ERROR(Format, ...) UE_LOG(LogCustom, Error, TEXT("%s %s"), *CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define	LOG_SCREEN(Format, ...) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(Format, ##__VA_ARGS__))
#define	LOG_SCREEN_COLOR(Color ,Format, ...) GEngine->AddOnScreenDebugMessage(-1, 5.f, Color, FString::Printf(Format, ##__VA_ARGS__))

UENUM(BlueprintType)
enum class EBlockSide : uint8
{
	Left,
	Right,
	Backward,
	Forward,
	Down,
	Up,
	
	Count
};

UENUM(BlueprintType)
enum class EBlockType : uint8
{
	Grass,
	Dirt,
	Stone,
	Sand,
	Coal,
	Iron,
	Gold,
	Diamond,
	BedRock,
	Water,
	Air,
};

UENUM(BlueprintType)
enum class EBlockState : uint8
{
	NoCrack,
	Crack1,
	Crack2,
	Crack3,
	Crack4,
};

UENUM(BlueprintType)
enum class EBlockTextureType : uint8
{
	GrassTop,
	GrassSide,
	Dirt,
	Stone,
	Sand,
	Coal,
	Iron,
	Gold,
	Diamond,
	BedRock,
	Water,
};

UENUM()
enum class EGraphRendererType : uint8
{
	None,
	Surface,
	Stone,
	DiamondTop,
	DiamondBottom,
};

USTRUCT(BlueprintType)
struct FMesh
{
	GENERATED_BODY()

public:
	void Empty()
	{
		Vertices.Empty();
		Triangles.Empty();
		Normals.Empty();
		UVs.Empty();
		Tangents.Empty();
		VertexColors.Empty();
	}

public:
	UPROPERTY(VisibleAnywhere)
	TArray<FVector> Vertices;

	UPROPERTY(VisibleAnywhere)
	TArray<int32> Triangles;
	
	UPROPERTY(VisibleAnywhere)
	TArray<FVector> Normals;

	UPROPERTY(VisibleAnywhere)
	TArray<FVector2D> UVs;

	UPROPERTY(VisibleAnywhere)
	TArray<FProcMeshTangent> Tangents;

	UPROPERTY(VisibleAnywhere)
	TArray<FColor> VertexColors;
};

USTRUCT(BlueprintType)
struct FGraphSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta=(ClampMin=0.f, ClampMax=1.f))
	float Scale = 0.f;

	UPROPERTY(EditAnywhere)
	float HeightScale = 0.f;

	UPROPERTY(EditAnywhere)
	int32 Octaves = 0;
	
	UPROPERTY(EditAnywhere)
	float HeightOffset = 0.f;
};

USTRUCT(BlueprintType)
struct FVoxel
{
	GENERATED_BODY()

public:
	static const FVector FLU;
	static const FVector FRU;
	static const FVector FLD;
	static const FVector FRD;
	static const FVector BLU;
	static const FVector BRU;
	static const FVector BLD;
	static const FVector BRD;

public:
	static const TArray<TArray<FVector2D>> BlockTextureUVs;

public:
	static const FIntVector ChunkCount;
	static const FIntVector BlockCount;
	static const float BlockSize;

public:
	static const int32 dx[];
	static const int32 dy[];
	static const int32 dz[];

public:
	static const float CoalPercent;
	static const float IronPercent;
	static const float GoldPercent;
	static const float DiamondPercent;
};
