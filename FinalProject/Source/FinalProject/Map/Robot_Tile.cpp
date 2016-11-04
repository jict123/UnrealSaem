// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "Robot_Tile.h"



ARobot_Tile::ARobot_Tile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileActor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileActor"));

	// Set StaticMesh Object
	static ConstructorHelpers::FObjectFinder <UStaticMesh>TileStaticMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	// Set Material Texture
	static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_(TEXT("Material'/Game/StarterContent/Materials/M_Tech_Panel.M_Tech_Panel'"));


	//Component Setting
	if (TileStaticMesh.Object) {
		TileActor->AttachTo(RootComponent);
		TileActor->SetStaticMesh(TileStaticMesh.Object);
		TileActor->SetMaterial(0, Material_.Object);
	}
}

void ARobot_Tile::NotifyActorOnClicked()
{
	FVector fLocation = TileActor->GetComponentLocation();

	UE_LOG(LogClass, Log, TEXT("%f,%f,%f"), fLocation.X, fLocation.Y, fLocation.Z);
}