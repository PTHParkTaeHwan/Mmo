// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnMine.h"

// Sets default values
ASpawnMine::ASpawnMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	RootComponent = Body;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BODY(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
	if (SM_BODY.Succeeded())
	{
		Body->SetStaticMesh(SM_BODY.Object);
	}

	


}

// Called when the game starts or when spawned
void ASpawnMine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

