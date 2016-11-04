// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FinalProjectGameMode.h"
#include "GameFramework/Actor.h"
#include "AnimalBuilding.generated.h"

UCLASS()
class FINALPROJECT_API AAnimalBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnimalBuilding();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	float GetHp() { return Hp; }
	void SetHp(float* hp) { Hp = *hp; }
protected:
	float Hp = 100.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TileCompoment)
	class UStaticMeshComponent* TileActor;
	float ConstLocationValue = 0.0f;
	AFinalProjectGameMode* hGameMode = Cast<AFinalProjectGameMode>(UGameplayStatics::GetGameMode(this));
	
};
