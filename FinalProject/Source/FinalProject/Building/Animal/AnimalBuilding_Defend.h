// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building/Animal/AnimalBuilding.h"
#include "AnimalBuilding_Defend.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AAnimalBuilding_Defend : public AAnimalBuilding
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AAnimalBuilding_Defend();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void NotifyActorOnClicked() override;

	TSubclassOf<class UUserWidget> MainUIWidgetClass;
	UPROPERTY()
		UUserWidget* MainUIWidget;
	
	
	
	
};
