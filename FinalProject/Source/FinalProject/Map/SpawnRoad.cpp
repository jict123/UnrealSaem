// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "SpawnRoad.h"
#include "Road_Tile.h"
#include "Human_Tile.h"
#include "Robot_Tile.h"
#include "Animal_Tile.h"
#include "AnimalGround.h"
#include "HumanGround.h"
#include "RobotGround.h"
#include "FinalProjectGameMode.h"

// Sets default values
ASpawnRoad::ASpawnRoad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawnRoad::BeginPlay()
{
	Super::BeginPlay();

	AnimalSpawn = AAnimalGround::StaticClass();
	hTileSpawn = AHuman_Tile::StaticClass();
	RoadSpawn = ARoad_Tile::StaticClass();
	HumanSpawn = AHumanGround::StaticClass();
	RobotSpawn = ARobotGround::StaticClass();
	rTileSpawn = ARobot_Tile::StaticClass();
	aTileSpawn = AAnimal_Tile::StaticClass();
	/*if (AnimalSpawn == NULL) {
		UE_LOG(LogClass, Log, TEXT("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"));
	}*/
	mRoadActorMap.Add('#', AnimalSpawn);
	mRoadActorMap.Add('$', hTileSpawn);
	mRoadActorMap.Add('%', RoadSpawn);
	mRoadActorMap.Add('^', HumanSpawn);
	mRoadActorMap.Add('&', RobotSpawn);
	mRoadActorMap.Add('*', rTileSpawn);
	mRoadActorMap.Add('!', aTileSpawn);

	mRoadActorMap.Add('0', RoadSpawn);
	mRoadActorMap.Add('1', RoadSpawn);
	mRoadActorMap.Add('2', RoadSpawn);
	mRoadActorMap.Add('3', RoadSpawn);
	mRoadActorMap.Add('4', RoadSpawn);
	mRoadActorMap.Add('5', RoadSpawn);
	mRoadActorMap.Add('6', RoadSpawn);

	SpawnRoadTile();
	
}

// Called every frame
void ASpawnRoad::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ASpawnRoad::SpawnRoadTile()
{
	AFinalProjectGameMode* sGameMode = Cast<AFinalProjectGameMode>(UGameplayStatics::GetGameMode(this));

	if (RoadSpawn != NULL)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			FVector SpawnLocation = FVector(0, 0, 0);

			FRotator SpawnRotation;
			SpawnRotation.Yaw = 0;
			SpawnRotation.Pitch = 0;
			SpawnRotation.Roll = 0;

			const FString& FullFilePath = FilePath;
			TArray<uint8> BinaryArray;
			
			if (!FFileHelper::LoadFileToArray(BinaryArray, *FullFilePath))
			{
				UE_LOG(LogClass, Log, TEXT("Load Fail"));
			}

			UE_LOG(LogClass, Log, TEXT("File Size = %d "), BinaryArray.Num());

			
			int x = 0, y = 0;

			int nLine;

			//---------1차원 배열로 받아온 맵을 2차원배열로 변경
			for (int i = 0; i < BinaryArray.Num(); i++)
			{
				if (BinaryArray[i] != '\n')
				{
					sGameMode->mSave[x][y] = BinaryArray[i] ;
				}

				nLine = i % 46;
				if (nLine != 44 || nLine != 45)
					y++;

				if (nLine == 45)
				{
					x ++;
					y = 0;
				}
			}
			//TMap<char, int> navigationCount;
			TArray<AActor*> Map0; TArray<AActor*> Map1; TArray<AActor*> Map2; TArray<AActor*> Map3; TArray<AActor*> Map4; TArray<AActor*> Map5; TArray<AActor*> Map6;
			
			//--------------2차원배열로 맵 스폰 및 맵정보 저장
			for (int i = 0; i < 44; i++)
			{
				//TArray<AActor*> oneLine;
				for (int j = 0; j < 44; j++)
				{
					char tileChar = sGameMode->mSave[i][j];

					//road spawn
					if(mRoadActorMap.Contains(tileChar))
					{
						UClass* roadActor = mRoadActorMap[tileChar];
						AActor* spawnRoad = World->SpawnActor<AActor>(roadActor, SpawnLocation, SpawnRotation, SpawnParams);

						//oneLine.Push(spawnRoad);

						// 다른 Path 처리 방식을 사용해야 할 것 같음
						switch (tileChar)
						{
						case '0':
						{
							Map0.Add(spawnRoad);
						}
						break;

						case '1':
						{
							Map1.Add(spawnRoad);
						}
						break;

						case '2':
						{
							Map2.Add(spawnRoad);
						}
						break;

						case '3':
						{
							Map3.Add(spawnRoad);
						}
						break;

						case '4':
						{
							Map4.Add(spawnRoad);
						}
						break;

						case '5':
						{
							Map5.Add(spawnRoad);
						}
						break;

						case '6':
						{
							Map6.Add(spawnRoad);
						}
						break;

						default:
						{

						}
						break;
						}
					}
					
					SpawnLocation.Y -= 100;
				}
				SpawnLocation.X += 100;
				SpawnLocation.Y = 0;
			}
			Algo::Reverse(Map1);
			Algo::Reverse(Map3);
			Algo::Reverse(Map4);
			Algo::Reverse(Map6);

			sGameMode->Target.Append(Map0);
			sGameMode->Target.Append(Map1);
			sGameMode->Target.Append(Map2);
			sGameMode->Target.Append(Map3);
			sGameMode->Target.Append(Map4);
			sGameMode->Target.Append(Map5);
			sGameMode->Target.Append(Map6);
		}
	}
}