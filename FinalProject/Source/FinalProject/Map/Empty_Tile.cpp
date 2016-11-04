// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "Empty_Tile.h"

// Sets default values
AEmpty_Tile::AEmpty_Tile()
{
}

// Called when the game starts or when spawned
void AEmpty_Tile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEmpty_Tile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	
}
	
void AEmpty_Tile::NotifyActorOnClicked()
{
	Super::NotifyActorOnClicked();
}
