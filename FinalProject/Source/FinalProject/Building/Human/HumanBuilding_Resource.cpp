// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "HumanBuilding_Resource.h"
#include "FinalProjectGameMode.h"


// Sets default values
AHumanBuilding_Resource::AHumanBuilding_Resource()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileActor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileActor"));

	// Set StaticMesh Object
	static ConstructorHelpers::FObjectFinder <UStaticMesh>TileStaticMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	// Set Material Texture
	static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_(TEXT("Material'/Game/StarterContent/Materials/M_Brick_Clay_Old.M_Brick_Clay_Old'"));

	//Component Setting
	if (TileStaticMesh.Object) {
		TileActor->AttachTo(RootComponent);
		TileActor->SetStaticMesh(TileStaticMesh.Object);
		TileActor->SetMaterial(0, Material_.Object);
		TileActor->SetWorldScale3D(FVector(3.0f, 3.0f, 2.0f));
	}
	TileActor->CastShadow = false;
	TileActor->SetCollisionObjectType(ECC_Destructible);

}

// Called when the game starts or when spawned
void AHumanBuilding_Resource::BeginPlay()
{
	Super::BeginPlay();

	tTime = 0.0f;
}

// Called every frame
void AHumanBuilding_Resource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Hp <= 0.0f)
		this->Destroy();

	tTime += DeltaTime;
	if (tTime > 1.0f) {
		hGameMode->fMachinePart += 3.0f;
		hGameMode->fManaStone += 1.5f;
		tTime = 0.0f;
	}
}
