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

const TArray<TArray<FVector2D>> FVoxel::BlockUVs =
{
	// Grass
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
	// Water
	{
		FVector2D(0.0625f * 14, 0.0625f * 12),	FVector2D(0.0625f * 15, 0.0625f * 12),
		FVector2D(0.0625f * 14, 0.0625f * 13),	FVector2D(0.0625f * 15, 0.0625f * 13),
	},
};
