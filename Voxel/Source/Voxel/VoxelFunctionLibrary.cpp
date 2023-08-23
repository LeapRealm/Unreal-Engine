#include "VoxelFunctionLibrary.h"

#include "Define.h"
#include "ProceduralMeshComponent.h"

void UVoxelFunctionLibrary::BuildQuad(EBlockSide Side, EBlockType Type, const FVector& Offset, FMesh& OutMesh)
{
	const FVector FLU = FVoxel::FLU + Offset;
	const FVector FRU = FVoxel::FRU + Offset;
	const FVector FLD = FVoxel::FLD + Offset;
	const FVector FRD = FVoxel::FRD + Offset;
	const FVector BLU = FVoxel::BLU + Offset;
	const FVector BRU = FVoxel::BRU + Offset;
	const FVector BLD = FVoxel::BLD + Offset;
	const FVector BRD = FVoxel::BRD + Offset;
	
	ClearMesh(OutMesh);
	OutMesh.Vertices.Reserve(4);
	OutMesh.Triangles.Reserve(6);
	OutMesh.Normals.Reserve(4);
	OutMesh.UVs.Reserve(4);
	
	switch (Side)
	{
	case EBlockSide::Forward:
		OutMesh.Vertices.Add(FRU);
		OutMesh.Vertices.Add(FLU);
		OutMesh.Vertices.Add(FRD);
		OutMesh.Vertices.Add(FLD);

		OutMesh.Normals.Add(FVector::ForwardVector);
		OutMesh.Normals.Add(FVector::ForwardVector);
		OutMesh.Normals.Add(FVector::ForwardVector);
		OutMesh.Normals.Add(FVector::ForwardVector);
		break;
	case EBlockSide::Backward:
		OutMesh.Vertices.Add(BLU);
		OutMesh.Vertices.Add(BRU);
		OutMesh.Vertices.Add(BLD);
		OutMesh.Vertices.Add(BRD);

		OutMesh.Normals.Add(FVector::BackwardVector);
		OutMesh.Normals.Add(FVector::BackwardVector);
		OutMesh.Normals.Add(FVector::BackwardVector);
		OutMesh.Normals.Add(FVector::BackwardVector);
		break;
	case EBlockSide::Down:
		OutMesh.Vertices.Add(BLD);
		OutMesh.Vertices.Add(BRD);
		OutMesh.Vertices.Add(FLD);
		OutMesh.Vertices.Add(FRD);

		OutMesh.Normals.Add(FVector::DownVector);
		OutMesh.Normals.Add(FVector::DownVector);
		OutMesh.Normals.Add(FVector::DownVector);
		OutMesh.Normals.Add(FVector::DownVector);
		break;
	case EBlockSide::Up:
		OutMesh.Vertices.Add(BRU);
		OutMesh.Vertices.Add(BLU);
		OutMesh.Vertices.Add(FRU);
		OutMesh.Vertices.Add(FLU);

		OutMesh.Normals.Add(FVector::UpVector);
		OutMesh.Normals.Add(FVector::UpVector);
		OutMesh.Normals.Add(FVector::UpVector);
		OutMesh.Normals.Add(FVector::UpVector);
		break;
	case EBlockSide::Left:
		OutMesh.Vertices.Add(FLU);
		OutMesh.Vertices.Add(BLU);
		OutMesh.Vertices.Add(FLD);
		OutMesh.Vertices.Add(BLD);

		OutMesh.Normals.Add(FVector::LeftVector);
		OutMesh.Normals.Add(FVector::LeftVector);
		OutMesh.Normals.Add(FVector::LeftVector);
		OutMesh.Normals.Add(FVector::LeftVector);
		break;
	case EBlockSide::Right:
		OutMesh.Vertices.Add(BRU);
		OutMesh.Vertices.Add(FRU);
		OutMesh.Vertices.Add(BRD);
		OutMesh.Vertices.Add(FRD);

		OutMesh.Normals.Add(FVector::RightVector);
		OutMesh.Normals.Add(FVector::RightVector);
		OutMesh.Normals.Add(FVector::RightVector);
		OutMesh.Normals.Add(FVector::RightVector);
		break;
	}

	OutMesh.Triangles = { 0, 2, 1, 1, 2, 3 };

	OutMesh.UVs.Add(FVoxel::BlockUVs[Type][0]);
	OutMesh.UVs.Add(FVoxel::BlockUVs[Type][1]);
	OutMesh.UVs.Add(FVoxel::BlockUVs[Type][2]);
	OutMesh.UVs.Add(FVoxel::BlockUVs[Type][3]);
}

void UVoxelFunctionLibrary::MergeMeshes(const TArray<FMesh>& Meshes, FMesh& OutMesh)
{
	TMap<FVertex, int32> VertexToOrder;
	TArray<int32> Triangles;

	int Order = 0;
	for (int32 i = 0; i < Meshes.Num(); i++)
	{
		if (Meshes[i].Triangles.IsEmpty())
			continue;

		for (int32 j = 0; j < Meshes[i].Vertices.Num(); j++)
		{
			FVertex Vertex = FVertex(Meshes[i].Vertices[j], Meshes[i].Normals[j], Meshes[i].UVs[j]);
			if (VertexToOrder.Contains(Vertex) == false)
			{
				VertexToOrder.Add(Vertex, Order);
				Order++;
			}
		}
		
		for (int32 k = 0; k < Meshes[i].Triangles.Num(); k++)
		{
			int32 Triangle = Meshes[i].Triangles[k];
			FVertex Vertex = FVertex(Meshes[i].Vertices[Triangle], Meshes[i].Normals[Triangle], Meshes[i].UVs[Triangle]);
			Triangles.Add(VertexToOrder[Vertex]);
		}
	}

	ClearMesh(OutMesh);
	ExtractArrays(VertexToOrder, OutMesh);
	OutMesh.Triangles = MoveTemp(Triangles);
}

void UVoxelFunctionLibrary::ExtractArrays(const TMap<FVertex, int32>& VertexToOrder, FMesh& OutMesh)
{
	OutMesh.Vertices.SetNum(VertexToOrder.Num());
	OutMesh.Normals.SetNum(VertexToOrder.Num());
	OutMesh.UVs.SetNum(VertexToOrder.Num());
	
	for (const TTuple<FVertex, int32>& Tuple : VertexToOrder)
	{
		OutMesh.Vertices[Tuple.Value] = Tuple.Key.Vertex;
		OutMesh.Normals[Tuple.Value] = Tuple.Key.Normal;
		OutMesh.UVs[Tuple.Value] = Tuple.Key.UV;
	}
}

void UVoxelFunctionLibrary::ClearMesh(FMesh& OutMesh)
{
	OutMesh.Vertices.Empty();
	OutMesh.Triangles.Empty();
	OutMesh.Normals.Empty();
	OutMesh.UVs.Empty();
	OutMesh.Triangles.Empty();
	OutMesh.VertexColors.Empty();
}

void UVoxelFunctionLibrary::CreateMeshSection(UProceduralMeshComponent* Component, const FMesh& Mesh)
{
	Component->CreateMeshSection(0, Mesh.Vertices, Mesh.Triangles, Mesh.Normals, Mesh.UVs, Mesh.VertexColors, Mesh.Tangents, true);
}
