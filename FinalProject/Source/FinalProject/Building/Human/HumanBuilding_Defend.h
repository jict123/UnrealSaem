// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building/Human/HumanBuilding.h"
#include "HumanBuilding_Defend.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AHumanBuilding_Defend : public AHumanBuilding
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AHumanBuilding_Defend();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void NotifyActorOnClicked() override;

	TSubclassOf<class UUserWidget> MainUIWidgetClass;
	UPROPERTY()
		UUserWidget* MainUIWidget;
	
	
};
