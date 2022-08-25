// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelCreator.h"
#include "Editor.h"
#include "ProceduralMeshComponent.h"
#include "FastNoiseLite.h"
#include "Runtime/Engine/Public/EngineGlobals.h"

void ALevelCreator::BorderClass(UClass* ItemToSpawn)
{
	int GridSizeX = 50;
	float TileSize = 1200.f;
	float TileSize2 = 400.f;
	float GridSizeX2 = GridSizeX * 3;
	float Xlocation = 0.f;
	float Ylocation = 0.f;
	float Subtract = 0.f;
	Subtract = (TileSize * GridSizeX) / 2;
	float MultiX = 0.f;
	float MultiY = 0.f;
	float result = 0.f;


	for (int32 i = -2; i < 0; i++)
	{
		MultiX = i * TileSize2;
		Xlocation = MultiX - Subtract;
		//result = sin(i * PI / 180) * FMath::FRandRange(0.f, 500.f);

		for (int32 y = -1; y < GridSizeX2; y++)
		{
			MultiY = y * TileSize2;
			Ylocation = MultiY - Subtract;
			FVector LocationP(Xlocation, Ylocation + 800, result - 300); // Goes onto the border at the beginning x-axis
			FVector LocationP2((-Xlocation), Ylocation + 800, result - 600); // End of border x-axis
			FVector LocationP3(Ylocation + 400, Xlocation + 800, result - 300); // End of border y-axis
			FVector LocationP4(Ylocation + 200, (-Xlocation) - 400, result - 300); // Start of border y-axis
			FRotator RotationP(0.f, 0.f, 0.f);
			GetWorld()->SpawnActor<AActor>(ItemToSpawn, LocationP, RotationP);
			GetWorld()->SpawnActor<AActor>(ItemToSpawn, LocationP2, RotationP);
			GetWorld()->SpawnActor<AActor>(ItemToSpawn, LocationP3, RotationP);
			GetWorld()->SpawnActor<AActor>(ItemToSpawn, LocationP4, RotationP);
		}
	}




}

void ALevelCreator::FloorClass(UClass* ItemToSpawn)
{

	int GridSizeX = 50;
	float TileSize = 1200.f;
	float Xlocation = 0.f;
	float Ylocation = 0.f;
	float Subtract = 0.f;
	Subtract = (TileSize * GridSizeX) / 2;
	float MultiX = 0.f;
	float MultiY = 0.f;
	float result = 0.f;


	for (int32 i = -1; i < GridSizeX + 2; i++)
	{
		MultiX = i * TileSize;
		Xlocation = MultiX - Subtract;
		//result = sin(i * PI / 180) * FMath::FRandRange(0.f, 500.f);

		for (int32 y = -2; y < GridSizeX + 1; y++)
		{
			MultiY = y * TileSize;
			Ylocation = MultiY - Subtract;
			FVector LocationP(Xlocation, Ylocation, result);
			FRotator RotationP(0.f, 0.f, 0.f);
			GetWorld()->SpawnActor<AActor>(ItemToSpawn, LocationP, RotationP);
		}
	}
}

void ALevelCreator::TreeClass(UClass* ItemToSpawn)
{

	float TileSize = 1200.f;
	int32 GridSizeX = 45;
	float Xlocation = 0.f;
	float Ylocation = 0.f;
	float Subtract = 0.f;
	Subtract = (TileSize * GridSizeX) / 2;
	float MultiX = 0.f;
	float MultiY = 0.f;
	float result = 0.f;


	for (int32 i = 0; i < GridSizeX; i++)
	{
		MultiX = i * TileSize;
		Xlocation = MultiX - Subtract;
		//result = sin(i * PI / 180) * FMath::FRandRange(0.f, 500.f);

		for (int32 y = 0; y < GridSizeX; y++)
		{
			MultiY = y * TileSize;
			Ylocation = MultiY - Subtract;
			result = (Noise->GetNoise(Xlocation + y * 33, Ylocation + i * 33) * 1200);
			//result = (Noise->GetNoise(i * 5.f, y * 5.f) * 1200 );// -120.f;
			FVector LocationP(Xlocation, Ylocation + 1200, result - 30);
			FRotator RotationP(0.f, 0.f, 0.f);
			GetWorld()->SpawnActor<AActor>(ItemToSpawn, LocationP, RotationP);

		}
	}


}

// Sets default values
ALevelCreator::ALevelCreator()
{
	LevelRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProceduralMesh"));


	Noise = new FastNoiseLite();
	Noise->SetFrequency(.00006f);
	Noise->SetSeed(1337);
	Noise->SetFractalOctaves(6);
	Noise->SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	Noise->SetFractalType(FastNoiseLite::FractalType_FBm);


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelCreator::BeginPlay()
{
	Super::BeginPlay();
	FloorClass(Floor);
	TreeClass(Tree);
	BorderClass(Border);
}

// Called every frame
void ALevelCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

