// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "Road_Tile.h"


// Sets default values
ARoad_Tile::ARoad_Tile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileActor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileActor"));

	// Set StaticMesh Object
	static ConstructorHelpers::FObjectFinder <UStaticMesh>TileStaticMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	// Set Material Texture
	static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_(TEXT("Material'/Game/StarterContent/Materials/M_Ground_Gravel.M_Ground_Gravel'"));

	if (TileStaticMesh.Object) {
		TileActor->AttachTo(RootComponent);
		TileActor->SetStaticMesh(TileStaticMesh.Object);
		TileActor->SetMaterial(0, Material_.Object);
	}

}

// Called when the game starts or when spawned
void ARoad_Tile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoad_Tile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}