#pragma once

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
	Forward,
	Backward,
	Down,
	Up,
	Left,
	Right,
};

UENUM(BlueprintType)
enum EBlockType
{
	GrassTop,
	GrassSide,
	Dirt,
	Water,
	Stone,
	Sand,
};

USTRUCT(BlueprintType)
struct FMesh
{
	GENERATED_BODY()

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
struct FVertex
{
	GENERATED_BODY()

	FVertex() { }
	
	FVertex(const FVector& InVertex, const FVector& InNormal, const FVector2D& InUV)
		: Vertex(InVertex), Normal(InNormal), UV(InUV) { }

	bool operator==(const FVertex& Other) const
	{
		return (Vertex == Other.Vertex) && (Normal == Other.Normal) && (UV == Other.UV);
	}
	
	FORCEINLINE friend uint32 GetTypeHash(const FVertex& Vertex)
	{
		return FCrc::MemCrc32(&Vertex, sizeof(FVertex));
	}
	
	UPROPERTY(VisibleAnywhere)
	FVector Vertex = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere)
	FVector Normal = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere)
	FVector2D UV = FVector2D::ZeroVector;
};

USTRUCT(BlueprintType)
struct FVoxel
{
	GENERATED_BODY()

	static const FVector FLU;
	static const FVector FRU;
	static const FVector FLD;
	static const FVector FRD;
	static const FVector BLU;
	static const FVector BRU;
	static const FVector BLD;
	static const FVector BRD;
	
	static const TArray<TArray<FVector2D>> BlockUVs;
};
