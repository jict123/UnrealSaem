// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building/Human/HumanBuilding.h"
#include "HumanBuilding_Resource.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AHumanBuilding_Resource : public AHumanBuilding
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AHumanBuilding_Resource();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
private:
	float tTime;
	
	
};
