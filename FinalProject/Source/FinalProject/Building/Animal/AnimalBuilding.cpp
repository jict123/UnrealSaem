// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "AnimalBuilding.h"


// Sets default values
AAnimalBuilding::AAnimalBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAnimalBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAnimalBuilding::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (Hp <= 0.0f)
		this->Destroy();
}

