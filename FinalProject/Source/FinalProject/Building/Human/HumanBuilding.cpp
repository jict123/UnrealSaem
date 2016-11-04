// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "HumanBuilding.h"
#include "Character/Human/HumanCharacter1.h"
#include "Character/Human/HumanCharacter2.h"
#include "FinalProjectGameMode.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include<UMG.h>

// Sets default values
AHumanBuilding::AHumanBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHumanBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHumanBuilding::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	
}

void AHumanBuilding::NotifyActorOnClicked()
{
}
