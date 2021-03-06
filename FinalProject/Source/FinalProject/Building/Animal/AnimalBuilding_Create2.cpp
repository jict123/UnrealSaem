// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "AnimalBuilding_Create2.h"
#include "FinalProjectGameMode.h"
#include<UMG.h>

// Sets default values
AAnimalBuilding_Create2::AAnimalBuilding_Create2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileActor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileActor"));

	// Set StaticMesh Object
	static ConstructorHelpers::FObjectFinder <UStaticMesh>TileStaticMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	// Set Material Texture
	static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_(TEXT("Material'/Game/StarterContent/Materials/M_Ground_Gravel.M_Ground_Gravel'"));

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
void AAnimalBuilding_Create2::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAnimalBuilding_Create2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAnimalBuilding_Create2::NotifyActorOnClicked()
{

}



