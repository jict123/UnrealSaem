// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "FinalProjectGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AFinalProjectGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AFinalProjectGameMode();
	int nDifficult;
	float fMachinePart;
	float fManaStone;
	float fSoulStone;

	bool bHumanTile;

	bool bRe;

	bool Human3;
	bool HumanCreate3;
	//AActor* SaveMap[44][44];	

	char mSave[44][44]; //맵 정보 저장할 배열
	//TArray(AActor*) Target;
	TArray<AActor*> Target;

	FVector fLocation;
	bool HS1;

	/*UFUNCTION(BlueprintCallable, Category = "Start")
	void SetAI(int Df) { nDifficult = Df; }*/

	/*UFUNCTION(BlueprintCallable, Category = "resource")
	int GetAI() { return nDifficult; }*/
	/*UFUNCTION(BlueprintCallable, Category = "AI")
		void SetAAIDifficult(int DF) { nDifficult = DF; }*/

	UFUNCTION(BlueprintCallable, Category = "Start")
	void SetStart(bool bS) { bHumanTile = bS; }

	UFUNCTION(BlueprintCallable, Category = "BuildState")
	FVector GetBuildLocation() { return fLocation; }

	UFUNCTION(BlueprintCallable, Category = "resource")
	float GetPart() { return fMachinePart; }

	UFUNCTION(BlueprintCallable, Category = "resource")
	float GetMana() { return fManaStone; }

	UFUNCTION(BlueprintCallable, Category = "resource")
	float GetSoul() { return fSoulStone; }

	UFUNCTION(BlueprintCallable, Category = "resource")
	bool GetHuman3() { return HumanCreate3; }

	UFUNCTION(BlueprintCallable, Category = "resource")
	bool MakeResource(float P,float M,float S) {
		if (fMachinePart >= P && fManaStone >= M && fSoulStone >= S) {
			fMachinePart = fMachinePart - P;
			fManaStone = fManaStone - M;
			fSoulStone = fSoulStone - S;
			return true;
		}
		else 
			return false;
	}


	//void GetBuildLocation(bool Hs) { HS1 = Hs; }
	/*UFUNCTION(BlueprintCallable, Category = "AI|Navigation")
	static bool sSimpleMoveToActor(AController* Controller, const AActor* Goal);*/
};
