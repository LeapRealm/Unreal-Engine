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

const FIntVector FVoxel::BlockCount = FIntVector(16, 16, 16);
const FIntVector FVoxel::ChunkCount = FIntVector(20, 20, 10);
const float	FVoxel::BlockSize = 100.f;

const int32 FVoxel::DX[] = { +0, +0, -1, +1, +0, +0 };
const int32 FVoxel::DY[] = { -1, +1, +0, +0, +0, +0 };
const int32 FVoxel::DZ[] = { +0, +0, +0, +0, -1, +1 };

const float FVoxel::CoalPercent = 8.f;
const float FVoxel::IronPercent = 4.f;
const float FVoxel::GoldPercent = 2.f;
const float FVoxel::DiamondPercent = 1.f;
const float FVoxel::CavePercent = 15.f;

/*
(Scale=0.001000,HeightScale=5.887208,Octaves=8,HeightOffset=20.000000,DrawCutOff=0.000000)
(Scale=0.001000,HeightScale=3.668292,Octaves=9,HeightOffset=12.682276,DrawCutOff=0.000000)
(Scale=0.001000,HeightScale=1.853949,Octaves=8,HeightOffset=4.000000,DrawCutOff=0.000000)
(Scale=0.001000,HeightScale=1.853949,Octaves=8,HeightOffset=1.000000,DrawCutOff=0.000000)
(Scale=0.080000,HeightScale=2.000000,Octaves=2,HeightOffset=1.000000,DrawCutOff=0.200000)
*/