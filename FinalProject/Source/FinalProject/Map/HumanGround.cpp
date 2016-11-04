// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "HumanGround.h"




// Sets default values
AHumanGround::AHumanGround()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileActor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileActor"));

	nMaterial = FMath::RandRange(1, 3);
	// Set StaticMesh Object
	static ConstructorHelpers::FObjectFinder <UStaticMesh>TileStaticMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	// Set Material Texture
	static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_(TEXT("Material'/Game/StarterContent/Materials/M_CobbleStone_Pebble.M_CobbleStone_Pebble'"));
	static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_2(TEXT("Material'/Game/StarterContent/Materials/M_CobbleStone_Rough.M_CobbleStone_Rough'"));
	static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_3(TEXT("Material'/Game/StarterContent/Materials/M_CobbleStone_Smooth.M_CobbleStone_Smooth'"));

	if (TileStaticMesh.Object) {
		TileActor->AttachTo(RootComponent);
		TileActor->SetStaticMesh(TileStaticMesh.Object);
		if (nMaterial == 1)
			TileActor->SetMaterial(0, Material_.Object);
		else if (nMaterial == 2)
			TileActor->SetMaterial(0, Material_2.Object);
		else
			TileActor->SetMaterial(0, Material_3.Object);
	}

}