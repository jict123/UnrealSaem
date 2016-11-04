// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "HumanCharacter.h"
#include "Character/Human/HumanAIController.h"
#include "FinalProjectGameMode.h"
#include "BehaviorTree/HumanBehaviorTree.h"
// Sets default values
AHumanCharacter::AHumanCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
}

// Called when the game starts or when spawned
void AHumanCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AHumanCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Called to bind functionality to input
void AHumanCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AHumanCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

