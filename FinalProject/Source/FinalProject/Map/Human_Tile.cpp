// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "Human_Tile.h"
#include "FinalProjectGameMode.h"
#include "Building/Human/HumanBuilding.h"
#include "HumanGround.h"
//#include "UMG.h"
#include<UMG.h>
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"

//PrivateDependencyModuleNames.AddRange(new string[]{ "UMG" });
//#include"Slate.h"
//#include"Runtime/UMG/Public/UMG.h"
// including "Slate.h" is deprecated
#/*include "SlateBasics.h"
#include "Runtime/UMG/Public/UMG.h"
// maybe I need this?
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"*/

AHuman_Tile::AHuman_Tile()
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
	}

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

void AHuman_Tile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHuman_Tile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//void AHuman_Tile::Clicked(UPrimitiveComponent* pComponent)
//{
//	UE_LOG(LogClass, Log, TEXT("Clicked"));
//	static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_(TEXT("Material'/Game/StarterContent/Materials/M_Ground_Moss.M_Ground_Moss'"));
//	TileActor->SetWorldLocation(FVector(200.0f, 200.0f, 200.0f));
//	TileActor->SetMaterial(0, Material_.Object);
//}

void AHuman_Tile::NotifyActorOnClicked()
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
	//UWidgetLayoutLibrary::RemoveAllWidgets(GWorld->GetWorld());
	int x = 0, y = 0;
	//UE_LOG(LogClass, Log, TEXT("Clicked"));
	AFinalProjectGameMode* hGameMode = Cast<AFinalProjectGameMode>(UGameplayStatics::GetGameMode(this));
	//hGameMode->bHumanTile = true;

	FRotator SpawnRotation(0, 0, 0);
	FVector SpawnLocation = TileActor->GetComponentLocation();

	x = SpawnLocation.X*0.01f;
	y = SpawnLocation.Y*-0.01f;


	if (hGameMode->mSave[x][y - 1] != '$' && hGameMode->mSave[x][y + 1] == '$'  && hGameMode->mSave[x + 1][y] == '$' && hGameMode->mSave[x - 1][y] != '$')
	{
		SpawnLocation.Y -= 100.0f;
		SpawnLocation.X += 100.0f;
	}
	
	else if (hGameMode->mSave[x][y - 1] == '$' && hGameMode->mSave[x][y + 1] == '$' && hGameMode->mSave[x + 1][y] == '$' && hGameMode->mSave[x - 1][y] != '$')
	{
		SpawnLocation.X += 100.0f;
	}

	else if (hGameMode->mSave[x][y - 1] == '$' && hGameMode->mSave[x][y + 1] != '$' && hGameMode->mSave[x + 1][y] == '$' && hGameMode->mSave[x - 1][y] != '$')
	{
		SpawnLocation.Y += 100.0f;
		SpawnLocation.X += 100.0f;
	}

	else if (hGameMode->mSave[x][y - 1] != '$' && hGameMode->mSave[x][y + 1] == '$' && hGameMode->mSave[x + 1][y] == '$' && hGameMode->mSave[x - 1][y] == '$')
	{
		SpawnLocation.Y -= 100.0f;
	}

	else if (hGameMode->mSave[x][y - 1] == '$' && hGameMode->mSave[x][y + 1] != '$' && hGameMode->mSave[x + 1][y] == '$' && hGameMode->mSave[x - 1][y] == '$')
	{
		SpawnLocation.Y += 100.0f;
	}

	else if (hGameMode->mSave[x][y - 1] != '$' && hGameMode->mSave[x][y + 1] == '$' && hGameMode->mSave[x + 1][y] != '$' && hGameMode->mSave[x - 1][y] == '$')
	{
		SpawnLocation.Y -= 100.0f;
		SpawnLocation.X -= 100.0f;
	}

	else if (hGameMode->mSave[x][y - 1] == '$' && hGameMode->mSave[x][y + 1] == '$' && hGameMode->mSave[x + 1][y] != '$' && hGameMode->mSave[x - 1][y] == '$')
	{
		SpawnLocation.X -= 100.0f;
	}

	else if (hGameMode->mSave[x][y - 1] == '$' && hGameMode->mSave[x][y + 1] != '$' && hGameMode->mSave[x + 1][y] != '$' && hGameMode->mSave[x - 1][y] == '$')
	{
		SpawnLocation.Y += 100.0f;
		SpawnLocation.X -= 100.0f;
	}

	SpawnLocation.Z = 100.0f;
	//GWorld->SpawnActor<AHumanBuilding>(SpawnLocation, SpawnRotation);
	
	hGameMode->fLocation = SpawnLocation;

	MainUIWidget = CreateWidget<UUserWidget>(GetWorld(), MainUIWidgetClass2);
	MainUIWidget->AddToViewport();

	//CreateWidget

	//UE_LOG(LogClass, Log, TEXT("%f %f %f"), SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);
}