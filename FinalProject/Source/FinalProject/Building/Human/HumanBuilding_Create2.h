// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building/Human/HumanBuilding.h"
#include "HumanBuilding_Create2.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AHumanBuilding_Create2 : public AHumanBuilding
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AHumanBuilding_Create2();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void NotifyActorOnClicked() override;

	TSubclassOf<class UUserWidget> MainUIWidgetClass;
	TSubclassOf<class UUserWidget> MainUIWidgetClass1;
	TSubclassOf<class UUserWidget> MainUIWidgetClass2;
	UPROPERTY()
		UUserWidget* MainUIWidget;
	
	
	
};
