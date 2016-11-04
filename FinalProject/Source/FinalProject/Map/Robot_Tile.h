// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Map/Empty_Tile.h"
#include "Robot_Tile.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API ARobot_Tile : public AEmpty_Tile
{
	GENERATED_BODY()
	
public:
	ARobot_Tile();
	
	virtual void NotifyActorOnClicked() override;
};
