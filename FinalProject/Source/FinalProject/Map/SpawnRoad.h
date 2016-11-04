// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "FileManager.h"
#include "Road_Tile.h"
#include "Human_Tile.h"
#include "Robot_Tile.h"
#include "Animal_Tile.h"
#include "AnimalGround.h"
#include "HumanGround.h"
#include "RobotGround.h"
#include "GameFramework/Actor.h"
#include "SpawnRoad.generated.h"

UCLASS()
class FINALPROJECT_API ASpawnRoad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnRoad();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	UPROPERTY(EditAnywhere, Category = Spawning)
	TSubclassOf<class ARoad_Tile> RoadSpawn;

	UPROPERTY(EditAnywhere, Category = Spawning)
	TSubclassOf<class AHuman_Tile> hTileSpawn;

	UPROPERTY(EditAnywhere, Category = Spawning)
	TSubclassOf<class AAnimalGround> AnimalSpawn;

	UPROPERTY(EditAnywhere, Category = Spawning)
	TSubclassOf<class AHumanGround> HumanSpawn;

	UPROPERTY(EditAnywhere, Category = Spawning)
	TSubclassOf<class ARobotGround> RobotSpawn;

	UPROPERTY(EditAnywhere, Category = Spawning)
	TSubclassOf<class ARobot_Tile> rTileSpawn;

	UPROPERTY(EditAnywhere, Category = Spawning)
	TSubclassOf<class AAnimal_Tile> aTileSpawn;

	FString FilePath = "D:\\Unreal Projects\\FinalProject\\Source\\FinalProject\\Map\\Map.txt";
private:
	int nSpawn[44][44];

	void SpawnRoadTile();

	TMap<char, UClass*>  mRoadActorMap;
};
