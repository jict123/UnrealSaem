// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "FinalProjectPlayerController.h"

AFinalProjectPlayerController::AFinalProjectPlayerController()
{
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	bEnableMouseOverEvents = true;
	bShowMouseCursor = true;

	//DefaultClickTraceChannel = ECC_Visibility;

	HitResultTraceDistance = 100000.0f;
}

