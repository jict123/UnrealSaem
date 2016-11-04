// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building/Animal/AnimalBuilding.h"
#include "AnimalBuilding_Create3.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AAnimalBuilding_Create3 : public AAnimalBuilding
{
	GENERATED_BODY()
private:
	float f_time;
public:
	// Sets default values for this actor's properties
	AAnimalBuilding_Create3();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void NotifyActorOnClicked() override;

	TSubclassOf<class UUserWidget> MainUIWidgetClass;
	UPROPERTY()
		UUserWidget* MainUIWidget;
	
	
	
	
};
