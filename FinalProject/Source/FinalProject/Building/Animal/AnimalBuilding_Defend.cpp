// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "AnimalBuilding_Defend.h"
#include "FinalProjectGameMode.h"
#include<UMG.h>

// Sets default values
AAnimalBuilding_Defend::AAnimalBuilding_Defend()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileActor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileActor"));

	// Set StaticMesh Object
	static ConstructorHelpers::FObjectFinder <UStaticMesh>TileStaticMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	// Set Material Texture
	static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_(TEXT("Material'/Game/StarterContent/Materials/M_Wood_Pine.M_Wood_Pine'"));

	//Component Setting
	if (TileStaticMesh.Object) {
		TileActor->AttachTo(RootComponent);
		//TileActor->OnClicked.AddDynamic(this, &AHuman_Tile::Clicked);
		TileActor->SetStaticMesh(TileStaticMesh.Object);
		TileActor->SetMaterial(0, Material_.Object);
		TileActor->SetWorldScale3D(FVector(3.0f, 3.0f, 2.0f));
	}
	TileActor->CastShadow = false;
	TileActor->SetCollisionObjectType(ECC_Destructible);

}

// Called when the game starts or when spawned
void AAnimalBuilding_Defend::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAnimalBuilding_Defend::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAnimalBuilding_Defend::NotifyActorOnClicked()
{

}







