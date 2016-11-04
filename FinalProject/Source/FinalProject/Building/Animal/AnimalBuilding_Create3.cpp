// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "AnimalBuilding_Create3.h"
#include "FinalProjectGameMode.h"
#include<UMG.h>
#include "Character/Animal/AnimalCharacter5.h"
// Sets default values
AAnimalBuilding_Create3::AAnimalBuilding_Create3()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileActor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileActor"));

	// Set StaticMesh Object
	static ConstructorHelpers::FObjectFinder <UStaticMesh>TileStaticMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	// Set Material Texture
	static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_(TEXT("Material'/Game/StarterContent/Materials/M_Ground_Moss.M_Ground_Moss'"));

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
void AAnimalBuilding_Create3::BeginPlay()
{
	Super::BeginPlay();

	f_time = 30.0f;
	hGameMode->HumanCreate3 = true;

}

// Called every frame
void AAnimalBuilding_Create3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Hp <= 0.0f) {
		hGameMode->HumanCreate3 = false;
		this->Destroy();
	}
	if (hGameMode->Human3 == false) {
		f_time += DeltaTime;
		if (f_time > 30.0f) {
			FRotator SpawnRotation(0, 0, 0);
			FVector SpawnLocation = TileActor->GetComponentLocation();
			SpawnLocation.Z = 150;

			int x = 0, y = 0;

			x = SpawnLocation.X * 0.01f;
			y = SpawnLocation.Y * -0.01f;

			if (hGameMode->mSave[x + 2][y] == '%')
			{
				SpawnLocation.X += 300.0f;
			}

			else if (hGameMode->mSave[x - 2][y] == '%')
			{
				SpawnLocation.X -= 300.0f;
			}

			else if (hGameMode->mSave[x][y + 2] == '%')
			{
				SpawnLocation.Y -= 300.0f;
			}

			else if (hGameMode->mSave[x][y - 2] == '%')
			{
				SpawnLocation.Y += 300.0f;
			}

			else if (hGameMode->mSave[x + 2][y + 2] == '%')
			{
				SpawnLocation.Y -= 300.0f;
				SpawnLocation.X += 300.0f;
			}

			else if (hGameMode->mSave[x - 2][y - 2] == '%')
			{
				SpawnLocation.Y += 300.0f;
				SpawnLocation.X -= 300.0f;
			}

			else if (hGameMode->mSave[x + 2][y + 2] == '%')
			{
				SpawnLocation.Y -= 300.0f;
				SpawnLocation.X += 300.0f;
			}

			else if (hGameMode->mSave[x + 2][y - 2] == '%')
			{
				SpawnLocation.Y += 300.0f;
				SpawnLocation.X += 300.0f;
			}

			else if (hGameMode->mSave[x - 2][y + 2] == '%')
			{
				SpawnLocation.Y -= 300.0f;
				SpawnLocation.X -= 300.0f;
			}
			AAnimalCharacter5* hCharacter = GWorld->SpawnActor<AAnimalCharacter5>(SpawnLocation, SpawnRotation);
			if (hCharacter->Controller == NULL)
			{
				hCharacter->SpawnDefaultController();
			}
			f_time = 0.0f;
		}
	}
}

void AAnimalBuilding_Create3::NotifyActorOnClicked()
{

}



