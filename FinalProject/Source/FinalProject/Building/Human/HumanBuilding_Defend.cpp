// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "HumanBuilding_Defend.h"
#include "Character/Human/HumanCharacter.h"
#include "Character/Animal/AnimalCharacter.h"
#include "FinalProjectGameMode.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include<UMG.h>
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AHumanBuilding_Defend::AHumanBuilding_Defend()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileActor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileActor"));

	// Set StaticMesh Object
	static ConstructorHelpers::FObjectFinder <UStaticMesh>TileStaticMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	// Set Material Texture
	static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Steel.M_Metal_Steel'"));

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
	if (MainUIWidgetFinder.Succeeded())
	{
		MainUIWidgetClass = MainUIWidgetFinder.Object;
	}
}

// Called when the game starts or when spawned
void AHumanBuilding_Defend::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AHumanBuilding_Defend::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Hp <= 0.0f)
		this->Destroy();

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	TArray<AActor*> A;
	TArray<AActor*> B;
	TArray<AActor*> ActorsToIgnore;
	UGameplayStatics::GetAllActorsOfClass(GWorld->GetWorld(), AHumanCharacter::StaticClass(), A);
	UGameplayStatics::GetAllActorsOfClass(GWorld->GetWorld(), AHumanBuilding::StaticClass(), B);
	ActorsToIgnore.Append(A);
	ActorsToIgnore.Append(B);
	FHitResult OutHits;

	bool Agro = UKismetSystemLibrary::SphereTraceSingleForObjects(GWorld->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + FVector(0.0f, 0.0f, 10.0f), 300.0f, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);
	if (Agro == true) {
		if (OutHits.GetActor()->IsA(AAnimalCharacter::StaticClass())) {
			AAnimalCharacter* animal = Cast<AAnimalCharacter>(OutHits.GetActor());
			float hp = animal->GetHp() - 0.5f;
			animal->SetHp(&hp);
		}
	}
}

void AHumanBuilding_Defend::NotifyActorOnClicked()
{
}








