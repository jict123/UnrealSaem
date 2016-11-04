// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Road_Tile.generated.h"

UCLASS()
class FINALPROJECT_API ARoad_Tile : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TileCompoment)
	class UStaticMeshComponent* TileActor;
	float ConstLocationValue = 0.0f;

	// Sets default values for this actor's properties
	ARoad_Tile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;	
};
