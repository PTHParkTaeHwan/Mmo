// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnMine.generated.h"

UCLASS()
class TESTMMO_API ASpawnMine : public AActor
{
	GENERATED_BODY()
	//==============
	//  함수 선언  //
	//==============

public:	
	// Sets default values for this actor's properties
	ASpawnMine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	//==============
	//  변수 선언  //
	//==============
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *Body;
};
