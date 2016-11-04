// Fill out your copyright notice in the Description page of Project Settings.
#include "FinalProject.h"
#include "HumanBuilding_Create1.h"
#include "Character/Human/HumanCharacter1.h"
#include "Character/Human/HumanCharacter2.h"
#include "FinalProjectGameMode.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include<UMG.h>
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"

// Sets default values
AHumanBuilding_Create1::AHumanBuilding_Create1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileActor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileActor"));

	// Set StaticMesh Object
	static ConstructorHelpers::FObjectFinder <UStaticMesh>TileStaticMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	// Set Material Texture
	static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_(TEXT("Material'/Game/StarterContent/Materials/M_Brick_Clay_New.M_Brick_Clay_New'"));

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

	static ConstructorHelpers::FObjectFinder<UClass> MainUIWidgetFinder(TEXT("WidgetBlueprint'/Game/FinalProject/UI/HumanCreateMenu1.HumanCreateMenu1_C'"));
	static ConstructorHelpers::FObjectFinder<UClass> MainUIWidgetFinder1(TEXT("WidgetBlueprint'/Game/FinalProject/UI/HumanCreateMenu2.HumanCreateMenu2_C'"));
	static ConstructorHelpers::FObjectFinder<UClass> MainUIWidgetFinder2(TEXT("WidgetBlueprint'/Game/FinalProject/UI/HumanStructureMenu.HumanStructureMenu_C'"));
	if (MainUIWidgetFinder.Succeeded())
	{
		MainUIWidgetClass = MainUIWidgetFinder.Object;
	}
	if (MainUIWidgetFinder1.Succeeded())
	{
		MainUIWidgetClass1 = MainUIWidgetFinder1.Object;
	}
	if (MainUIWidgetFinder2.Succeeded())
	{
		MainUIWidgetClass2 = MainUIWidgetFinder2.Object;
	}
	
}

// Called when the game starts or when spawned
void AHumanBuilding_Create1::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AHumanBuilding_Create1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Hp <= 0.0f)
		this->Destroy();
}

void AHumanBuilding_Create1::NotifyActorOnClicked()
{
	TArray<UUserWidget*> tWidget;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GWorld->GetWorld(), tWidget, MainUIWidgetClass);
	for (int i = 0; i < tWidget.Num(); i++) {
		tWidget[i]->RemoveFromParent();
	}
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GWorld->GetWorld(), tWidget, MainUIWidgetClass1);
	for (int i = 0; i < tWidget.Num(); i++) {
		tWidget[i]->RemoveFromParent();
	}
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GWorld->GetWorld(), tWidget, MainUIWidgetClass2);
	for (int i = 0; i < tWidget.Num(); i++) {
		tWidget[i]->RemoveFromParent();
	}

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

	else if (hGameMode->mSave[x - 2][y- 2] == '%')
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

	hGameMode->fLocation = SpawnLocation;
	
	MainUIWidget = CreateWidget<UUserWidget>(GetWorld(), MainUIWidgetClass);
	MainUIWidget->AddToViewport();
}
