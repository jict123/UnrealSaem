// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building/Animal/AnimalBuilding.h"
#include "AnimalBuilding_Create2.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AAnimalBuilding_Create2 : public AAnimalBuilding
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AAnimalBuilding_Create2();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void NotifyActorOnClicked() override;

	TSubclassOf<class UUserWidget> MainUIWidgetClass;
	UPROPERTY()
		UUserWidget* MainUIWidget;
	
	
	
	
};
