// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ParentGround.generated.h"

UCLASS()
class FINALPROJECT_API AParentGround : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParentGround();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TileCompoment)
	class UStaticMeshComponent* TileActor;
	float ConstLocationValue = 0.0f;

	int nMaterial;
};
