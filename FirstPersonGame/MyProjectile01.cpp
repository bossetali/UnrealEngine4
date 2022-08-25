// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProjectile01.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AMyProjectile01::AMyProjectile01()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creating our Default Components
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ProjectileMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));



	SphereComponent->InitSphereRadius(5.0f);
	SphereComponent->BodyInstance.SetCollisionProfileName("Projectile");
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereComponent->OnComponentHit.AddDynamic(this, &AMyProjectile01::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	SphereComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	SphereComponent->CanCharacterStepUpOn = ECB_No;


	SetRootComponent(SphereComponent);


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = SphereComponent;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;



}

// Called when the game starts or when spawned
void AMyProjectile01::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyProjectile01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyProjectile01::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		//OtherActor->Destroy(); //Kill the hit actor
		Destroy();
	}

}

