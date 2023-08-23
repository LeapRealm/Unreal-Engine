#include "Block.h"

#include "Define.h"
#include "ProceduralMeshComponent.h"
#include "VoxelFunctionLibrary.h"

ABlock::ABlock()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProcMesh"));
}

void ABlock::BeginPlay()
{
	Super::BeginPlay();

	TArray<FMesh> QuadMeshes;
	QuadMeshes.SetNum(6);
	UVoxelFunctionLibrary::BuildQuad(EBlockSide::Forward,	EBlockType::GrassTop,	FVector(100, 100, 100), QuadMeshes[0]);
	UVoxelFunctionLibrary::BuildQuad(EBlockSide::Backward,	EBlockType::GrassSide,	FVector(100, 100, 100), QuadMeshes[1]);
	UVoxelFunctionLibrary::BuildQuad(EBlockSide::Down,		EBlockType::Water,		FVector(100, 100, 100), QuadMeshes[2]);
	UVoxelFunctionLibrary::BuildQuad(EBlockSide::Up,		EBlockType::Stone,		FVector(100, 100, 100), QuadMeshes[3]);
	UVoxelFunctionLibrary::BuildQuad(EBlockSide::Left,		EBlockType::Sand,		FVector(100, 100, 100), QuadMeshes[4]);
	UVoxelFunctionLibrary::BuildQuad(EBlockSide::Right,		EBlockType::Dirt,		FVector(100, 100, 100), QuadMeshes[5]);

	FMesh BlockMesh;
	UVoxelFunctionLibrary::MergeMeshes(QuadMeshes, BlockMesh);
	UVoxelFunctionLibrary::CreateMeshSection(ProceduralMeshComponent, BlockMesh);

	ProceduralMeshComponent->SetMaterial(0, Material);
}
