// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "RobotGround.h"

ARobotGround::ARobotGround()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileActor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileActor"));

	nMaterial = FMath::RandRange(1, 2);
	// Set StaticMesh Object
	static ConstructorHelpers::FObjectFinder <UStaticMesh>TileStaticMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	// Set Material Texture 
	static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_(TEXT("Material'/Game/StarterContent/Materials/M_Tech_Hex_Tile_Pulse.M_Tech_Hex_Tile_Pulse'"));
	static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_2(TEXT("Material'/Game/StarterContent/Materials/M_Tech_Hex_Tile.M_Tech_Hex_Tile'"));
	static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_3(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Steel.M_Metal_Steel'"));


	if (TileStaticMesh.Object) {
		TileActor->AttachTo(RootComponent);
		TileActor->SetStaticMesh(TileStaticMesh.Object);
		if (nMaterial == 1)
			TileActor->SetMaterial(0, Material_.Object);
		else if (nMaterial == 2)
			TileActor->SetMaterial(0, Material_2.Object);
		/*else
			TileActor->SetMaterial(0, Material_3.Object);*/
	}
}



