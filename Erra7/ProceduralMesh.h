// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ProceduralMeshComponent.h"
#include "FastNoiseLite.h"
#include "FastNoiseWrapper.h"

#include "ProceduralMesh.generated.h"

class FastNoiseLite;
class ProceduralMeshComponent;

UCLASS()
class ERRA7_003_API AProceduralMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralMesh();

	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInterface* Material;

	int PolySize = 5;
	int VerticesQuantity = 241;
	int HeightScale = 1200;
	int LOD = 3;

	float UVscale = 3.0f;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> normals;
	TArray<FVector2D> UVs;
	TArray<FColor> vertexColors;
	TArray<FProcMeshTangent> tangets;

protected:

	UPROPERTY(VisibleAnywhere)

	UProceduralMeshComponent* Mesh;
	FastNoiseLite* Noise;

	virtual void SpawninGrid();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
