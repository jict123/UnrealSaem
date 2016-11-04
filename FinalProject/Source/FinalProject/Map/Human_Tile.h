// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Map/Empty_Tile.h"
#include "Human_Tile.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AHuman_Tile : public AEmpty_Tile
{
	GENERATED_BODY()
	
public:
	AHuman_Tile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void NotifyActorOnClicked() override;

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
		TSubclassOf<UUserWidget> WidgetTemplate;

	UPROPERTY()
		UUserWidget* WidgetInstance;*/
	TSubclassOf<class UUserWidget> MainUIWidgetClass;
	TSubclassOf<class UUserWidget> MainUIWidgetClass1;
	TSubclassOf<class UUserWidget> MainUIWidgetClass2;
	UPROPERTY()
	UUserWidget* MainUIWidget;

};
