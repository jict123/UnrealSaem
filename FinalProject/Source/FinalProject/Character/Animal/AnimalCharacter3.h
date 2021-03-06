// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/Animal/AnimalCharacter.h"
#include "AnimalCharacter3.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AAnimalCharacter3 : public AAnimalCharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AAnimalCharacter3();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	
	
};
