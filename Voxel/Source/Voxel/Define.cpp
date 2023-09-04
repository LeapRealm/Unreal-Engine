#include "Define.h"

DEFINE_LOG_CATEGORY(LogCustom);

const FVector FVoxel::FLU = FVector(+50.f, -50.f, +50.f);
const FVector FVoxel::FRU = FVector(+50.f, +50.f, +50.f);
const FVector FVoxel::FLD = FVector(+50.f, -50.f, -50.f);
const FVector FVoxel::FRD = FVector(+50.f, +50.f, -50.f);
const FVector FVoxel::BLU = FVector(-50.f, -50.f, +50.f);
const FVector FVoxel::BRU = FVector(-50.f, +50.f, +50.f);
const FVector FVoxel::BLD = FVector(-50.f, -50.f, -50.f);
const FVector FVoxel::BRD = FVector(-50.f, +50.f, -50.f);

const TArray<TArray<FVector2D>> FVoxel::BlockTextureUVs =
{
	// Grass Top
	{
		FVector2D(0.0625f * 2, 0.0625f * 9),	FVector2D(0.0625f * 3, 0.0625f * 9),
		FVector2D(0.0625f * 2, 0.0625f * 10),	FVector2D(0.0625f * 3, 0.0625f * 10),
	},
	// Grass Side
	{
		FVector2D(0.0625f * 3, 0.0625f * 0),	FVector2D(0.0625f * 4, 0.0625f * 0),
		FVector2D(0.0625f * 3, 0.0625f * 1),	FVector2D(0.0625f * 4, 0.0625f * 1),
	},
	// Dirt
	{
		FVector2D(0.0625f * 2, 0.0625f * 0),	FVector2D(0.0625f * 3, 0.0625f * 0),
		FVector2D(0.0625f * 2, 0.0625f * 1),	FVector2D(0.0625f * 3, 0.0625f * 1),
	},
	// Stone
	{
		FVector2D(0.0625f * 1, 0.0625f * 0),	FVector2D(0.0625f * 2, 0.0625f * 0),
		FVector2D(0.0625f * 1, 0.0625f * 1),	FVector2D(0.0625f * 2, 0.0625f * 1),
	},
	// Sand
	{
		FVector2D(0.0625f * 2, 0.0625f * 1),	FVector2D(0.0625f * 3, 0.0625f * 1),
		FVector2D(0.0625f * 2, 0.0625f * 2),	FVector2D(0.0625f * 3, 0.0625f * 2),
	},
	// Coal
	{
		FVector2D(0.0625f * 2, 0.0625f * 2),	FVector2D(0.0625f * 3, 0.0625f * 2),
		FVector2D(0.0625f * 2, 0.0625f * 3),	FVector2D(0.0625f * 3, 0.0625f * 3),
	},
	// Iron
	{
		FVector2D(0.0625f * 1, 0.0625f * 2),	FVector2D(0.0625f * 2, 0.0625f * 2),
		FVector2D(0.0625f * 1, 0.0625f * 3),	FVector2D(0.0625f * 2, 0.0625f * 3),
	},
	// Gold
	{
		FVector2D(0.0625f * 0, 0.0625f * 2),	FVector2D(0.0625f * 1, 0.0625f * 2),
		FVector2D(0.0625f * 0, 0.0625f * 3),	FVector2D(0.0625f * 1, 0.0625f * 3),
	},
	// Diamond
	{
		FVector2D(0.0625f * 2, 0.0625f * 3),	FVector2D(0.0625f * 3, 0.0625f * 3),
		FVector2D(0.0625f * 2, 0.0625f * 4),	FVector2D(0.0625f * 3, 0.0625f * 4),
	},
	// BedRock
	{
		FVector2D(0.0625f * 1, 0.0625f * 1),	FVector2D(0.0625f * 2, 0.0625f * 1),
		FVector2D(0.0625f * 1, 0.0625f * 2),	FVector2D(0.0625f * 2, 0.0625f * 2),
	},
	// Water
	{
		FVector2D(0.0625f * 14, 0.0625f * 12),	FVector2D(0.0625f * 15, 0.0625f * 12),
		FVector2D(0.0625f * 14, 0.0625f * 13),	FVector2D(0.0625f * 15, 0.0625f * 13),
	},
};

const FIntVector FVoxel::ChunkCount = FIntVector(10, 10, 10);
const FIntVector FVoxel::BlockCount = FIntVector(10, 10, 10);
const float	FVoxel::BlockSize = 100.f;

const int32 FVoxel::DX[] = { +0, +0, -1, +1, +0, +0 };
const int32 FVoxel::DY[] = { -1, +1, +0, +0, +0, +0 };
const int32 FVoxel::DZ[] = { +0, +0, +0, +0, -1, +1 };

const float FVoxel::CoalPercent = 15.f;
const float FVoxel::IronPercent = 10.f;
const float FVoxel::GoldPercent = 5.f;
const float FVoxel::DiamondPercent = 2.5f;
