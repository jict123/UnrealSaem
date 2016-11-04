// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "FPSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API UFPSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UFPSaveGame();
	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	/*UPROPERTY(VisibleAnywhere, Category = Basic)
	int nAIDifficult;*/
	
	
};
