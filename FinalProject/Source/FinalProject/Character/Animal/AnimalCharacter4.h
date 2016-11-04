// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/Animal/AnimalCharacter.h"
#include "AnimalCharacter4.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AAnimalCharacter4 : public AAnimalCharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AAnimalCharacter4();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	
	
};
