// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AMainHUD : public AHUD
{
	GENERATED_BODY()
public:
	AMainHUD();

	UPROPERTY()
	UFont* HUDFont;

	UPROPERTY()
	UTexture2D* ManaStone;
	UPROPERTY()
	UTexture2D* MachinePart;
	UPROPERTY()
	UTexture2D* SoulStone;

	virtual void DrawHUD() override;

private:
	int nMachinePart;
	int nManaStone;
	int nSoulStone;	
	
};
