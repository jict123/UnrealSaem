// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "HumanHUD.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AHumanHUD : public AHUD
{
	GENERATED_BODY()
public:
	AHumanHUD();

	UPROPERTY()
	UFont* hFont;
	
	virtual void DrawHUD() override;

	
};
