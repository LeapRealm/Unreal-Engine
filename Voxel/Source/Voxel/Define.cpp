﻿#include "Define.h"

DEFINE_LOG_CATEGORY(LogCustom);

const FIntVector FVoxel::BlockCount = FIntVector(32, 32, 32);
const FIntVector FVoxel::ChunkCount = FIntVector(20, 20, 8);
const int32	FVoxel::BlockSize = 100.f;

const int32 FVoxel::DX[] = { +0, +0, -1, +1, +0, +0 };
const int32 FVoxel::DY[] = { -1, +1, +0, +0, +0, +0 };
const int32 FVoxel::DZ[] = { +0, +0, +0, +0, -1, +1 };

const float FVoxel::CoalPercent = 6.f;
const float FVoxel::IronPercent = 3.f;
const float FVoxel::GoldPercent = 1.5f;
const float FVoxel::DiamondPercent = 0.75f;
const float FVoxel::CavePercent = 0.f;

const float FVoxel::StoneHeightOffset = 15.f;
const float FVoxel::DiamondHeightMin = 4;
const float FVoxel::DiamondHeightMax = 8;

const FFastNoiseSettings FVoxel::SurfaceNoiseSettings = { EFastNoise_NoiseType::SimplexFractal, 0.007, 5, 1.6, 0.5, 30, 200 };
const FPerlinNoiseSettings FVoxel::CaveNoiseSettings = { 0.12, 2, 2, 1, 0.25 };

const FVector FVoxel::FLU = FVector(+FVoxel::BlockSize, +000.f,				+FVoxel::BlockSize);
const FVector FVoxel::FRU = FVector(+FVoxel::BlockSize, +FVoxel::BlockSize, +FVoxel::BlockSize);
const FVector FVoxel::FLD = FVector(+FVoxel::BlockSize, +000.f,				+000.f);
const FVector FVoxel::FRD = FVector(+FVoxel::BlockSize, +FVoxel::BlockSize, +000.f);
const FVector FVoxel::BLU = FVector(+000.f,				+000.f,				+FVoxel::BlockSize);
const FVector FVoxel::BRU = FVector(+000.f,				+FVoxel::BlockSize, +FVoxel::BlockSize);
const FVector FVoxel::BLD = FVector(+000.f,				+000.f,				+000.f);
const FVector FVoxel::BRD = FVector(+000.f,				+FVoxel::BlockSize, +000.f);

const TArray<TArray<FVector2D>> FVoxel::BlockTextureUVs =
{
	// Grass Top
	{
		FVector2D(0.03125 * 2, 0.0625 * 0),	FVector2D(0.03125 * 3, 0.0625 * 0),
		FVector2D(0.03125 * 2, 0.0625 * 1),	FVector2D(0.03125 * 3, 0.0625 * 1),
	},
	// Grass Side
	{
		FVector2D(0.03125 * 6, 0.0625 * 0),	FVector2D(0.03125 * 7, 0.0625 * 0),
		FVector2D(0.03125 * 6, 0.0625 * 1),	FVector2D(0.03125 * 7, 0.0625 * 1),
	},
	// Dirt
	{
		FVector2D(0.03125 * 18, 0.0625 * 1), FVector2D(0.03125 * 19, 0.0625 * 1),
		FVector2D(0.03125 * 18, 0.0625 * 2), FVector2D(0.03125 * 19, 0.0625 * 2),
	},
	// Stone
	{
		FVector2D(0.03125 * 19, 0.0625 * 0), FVector2D(0.03125 * 20, 0.0625 * 0),
		FVector2D(0.03125 * 19, 0.0625 * 1), FVector2D(0.03125 * 20, 0.0625 * 1),
	},
	// Sand
	{
		FVector2D(0.03125 * 5, 0.0625 * 1),	FVector2D(0.03125 * 6, 0.0625 * 1),
		FVector2D(0.03125 * 5, 0.0625 * 2),	FVector2D(0.03125 * 6, 0.0625 * 2),
	},
	// Coal
	{
		FVector2D(0.03125 * 1, 0.0625 * 4),	FVector2D(0.03125 * 2, 0.0625 * 4),
		FVector2D(0.03125 * 1, 0.0625 * 5),	FVector2D(0.03125 * 2, 0.0625 * 5),
	},
	// Iron
	{
		FVector2D(0.03125 * 0, 0.0625 * 4),	FVector2D(0.03125 * 1, 0.0625 * 4),
		FVector2D(0.03125 * 0, 0.0625 * 5),	FVector2D(0.03125 * 1, 0.0625 * 5),
	},
	// Gold
	{
		FVector2D(0.03125 * 31, 0.0625 * 3), FVector2D(0.03125 * 32, 0.0625 * 3),
		FVector2D(0.03125 * 31, 0.0625 * 4), FVector2D(0.03125 * 32, 0.0625 * 4),
	},
	// Diamond
	{
		FVector2D(0.03125 * 3, 0.0625 * 4),	FVector2D(0.03125 * 4, 0.0625 * 4),
		FVector2D(0.03125 * 3, 0.0625 * 5),	FVector2D(0.03125 * 4, 0.0625 * 5),
	},
	// BedRock
	{
		FVector2D(0.03125 * 0, 0.0625 * 1),	FVector2D(0.03125 * 1, 0.0625 * 1),
		FVector2D(0.03125 * 0, 0.0625 * 2),	FVector2D(0.03125 * 1, 0.0625 * 2),
	},
};
