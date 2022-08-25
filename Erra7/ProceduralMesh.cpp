// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralMesh.h"

// Sets default values
AProceduralMesh::AProceduralMesh()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Mesh"));
	Mesh->bUseAsyncCooking = true;
	Mesh->SetCastShadow(false);
	SetRootComponent(Mesh);

	//Create a Blueprint option of changing a material
	Material = CreateDefaultSubobject<UMaterialInterface>(TEXT("Material"));


	Noise = new FastNoiseLite();
	Noise->SetFrequency(.00006f);
	Noise->SetSeed(1337);
	Noise->SetFractalOctaves(6);
	Noise->SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	Noise->SetFractalType(FastNoiseLite::FractalType_FBm);

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;


}

void AProceduralMesh::SpawninGrid()
{
	int meshSimplificationIncrement = (LOD == 0) ? 1 : LOD * 4;
	int vertPerLine = (VerticesQuantity - 1) / meshSimplificationIncrement + 1;


	for (int y = 0, i = 0; y < VerticesQuantity; y += meshSimplificationIncrement) {
		for (int x = 0; x < VerticesQuantity; x += meshSimplificationIncrement, i++) {



			float Height =
				Noise->GetNoise(
					(GetActorLocation().X + x * PolySize), (GetActorLocation().Y + y * PolySize)) * HeightScale;

			Vertices.Add(FVector(
				(x + ((VerticesQuantity - 1) / -2.f)) * PolySize, (y + ((VerticesQuantity - 1) / 2.f)) * PolySize,
				Height)
			);


			//UV's
			UVs.Add(FVector2D(x * UVscale / vertPerLine, y * UVscale / vertPerLine));

			//Triangles

			if (y < VerticesQuantity - 1 && x < VerticesQuantity - 1) {
				Triangles.Add(i);
				Triangles.Add(i + vertPerLine);
				Triangles.Add(i + 1);
				Triangles.Add(i + 1);
				Triangles.Add(i + vertPerLine);
				Triangles.Add(i + vertPerLine + 1);

			}

		}


	}
	//CreateMeshSection
	Mesh->UProceduralMeshComponent::CreateMeshSection(0, Vertices, Triangles, normals, UVs, vertexColors, tangets, true);



}


// Called when the game starts or when spawned
void AProceduralMesh::BeginPlay()
{
	SpawninGrid();
	Super::BeginPlay();
	Mesh->SetMaterial(0, Material);
}

// Called every frame
void AProceduralMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

