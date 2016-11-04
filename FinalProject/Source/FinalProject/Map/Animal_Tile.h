// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Map/Empty_Tile.h"
#include "Animal_Tile.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AAnimal_Tile : public AEmpty_Tile
{
	GENERATED_BODY()
	
public:
	AAnimal_Tile();
	
	virtual void NotifyActorOnClicked() override;
};
