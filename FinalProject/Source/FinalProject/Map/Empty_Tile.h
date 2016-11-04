// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Empty_Tile.generated.h"

UCLASS()
class FINALPROJECT_API AEmpty_Tile : public AActor
{
	GENERATED_BODY()
	
public:	
	//struct FAreaNavModifier* sNav;

	// Sets default values for this actor's properties
	AEmpty_Tile();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//virtual void NotifyActorOnClicked();
	virtual void NotifyActorOnClicked() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TileCompoment)
	class UStaticMeshComponent* TileActor;
	float ConstLocationValue = 0.0f;
};
