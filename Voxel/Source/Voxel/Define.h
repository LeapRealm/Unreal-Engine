#pragma once

#include "CoreMinimal.h"
#include "FastNoiseWrapper.h"
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
enum class ESide : uint8
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
	
	Count,
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
};

UENUM()
enum class ENoiseRendererType : uint8
{
	None,
	Surface,
	Stone,
	DiamondTop,
	DiamondBottom,
	Cave,
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
	static const FIntVector BlockCount;
	static const FIntVector ChunkCount;
	static const int32 BlockSize;

public:
	static const int32 DX[];
	static const int32 DY[];
	static const int32 DZ[];

public:
	static const float CoalPercent;
	static const float IronPercent;
	static const float GoldPercent;
	static const float DiamondPercent;
	static const float CavePercent;

	static const float StoneHeightOffset;
	static const float DiamondHeightMin;
	static const float DiamondHeightMax;

public:
	static const FFastNoiseSettings SurfaceNoiseSettings;
	static const FPerlinNoiseSettings CaveNoiseSettings;
};


USTRUCT(BlueprintType)
struct FMesh
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	TArray<FVector> Vertices;

	UPROPERTY(VisibleAnywhere)
	TArray<int32> Triangles;
	
	UPROPERTY(VisibleAnywhere)
	TArray<FVector> Normals;

	UPROPERTY(VisibleAnywhere)
	TArray<FVector2D> UVs;
};

USTRUCT(BlueprintType)
struct FPerlinNoiseSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	float Scale = 0.f;

	UPROPERTY(EditAnywhere)
	float HeightScale = 0.f;

	UPROPERTY(EditAnywhere)
	int32 Octaves = 0;
	
	UPROPERTY(EditAnywhere)
	float HeightOffset = 0.f;

	UPROPERTY(EditAnywhere)
	float DrawCutOff = 0.f;
};

USTRUCT(BlueprintType)
struct FFastNoiseSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	EFastNoise_NoiseType NoiseType = EFastNoise_NoiseType::Simplex;
	
	UPROPERTY(EditAnywhere)
	float Frequency = 0.f;

	UPROPERTY(EditAnywhere)
	int32 Octaves = 0;

	UPROPERTY(EditAnywhere)
	float Lacunarity = 0.f;

	UPROPERTY(EditAnywhere)
	float Gain = 0.f;
	
	UPROPERTY(EditAnywhere)
	float HeightScale = 0;

	UPROPERTY(EditAnywhere)
	float HeightOffset = 0;
};

USTRUCT(BlueprintType)
struct FChunkData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	TArray<EBlockType> BlockTypes;
};
