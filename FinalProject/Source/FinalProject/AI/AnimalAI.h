// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AnimalAI.generated.h"

UCLASS()
class FINALPROJECT_API AAnimalAI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnimalAI();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void InitScore();
	void CheckHuman();
	void CheckAnimal();
	void ActionAI(float fDeltatime);
	void AIAction(float fTime, int Difficult);
	FVector SpawnLocation(FVector vLocation);
	
	/*UFUNCTION(BlueprintCallable, Category = "resource")
		void SetAidifficult(int nDifficult) {
		nDifficult = nDifficult;
	}*/
private:
	float fHuman_Score;
	float fAnimal_Score;
	int nAnimal1;
	int nAnimal2;
	int nAnimal3;
	int nAnimal_Resource;
	int nAnimal_Defend;

	int nHumanUnit1;
	int nHumanUnit2;
	int nHumanUnit3;
	int nHumanUnit4;
	int nHumanUnit5;

	int nAnimalUnit1;
	int nAnimalUnit2;
	int nAnimalUnit3;
	int nAnimalUnit4;
	int nAnimalUnit5;

	float fPass;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	TArray<AActor*> A;
	TArray<AActor*> B;
	TArray<AActor*> C;
	TArray<AActor*> D;

	TArray<FHitResult> OutHits;
	TArray<FVector> vSpawn;
	TArray<FVector> vCreate1;
	TArray<FVector> vCreate2;

	float fMana;
	float fManaSecond;

	int nDifficult;
};
