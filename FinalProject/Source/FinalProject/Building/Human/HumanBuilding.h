// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FinalProjectGameMode.h"
#include "GameFramework/Actor.h"
#include "HumanBuilding.generated.h"

UCLASS()
class FINALPROJECT_API AHumanBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHumanBuilding();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void NotifyActorOnClicked() override;

	/*UPROPERTY(EditAnywhere, Category = Spawning)
	TSubclassOf<class AHumanCharacter> hCharacter;*/
	//TSubclassOf<class UHumanBehaviorTree> hBehaviort;
	
	float GetHp() { return Hp; }
	void SetHp(float* hp) { Hp = *hp; }
protected:
	float Hp = 100.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TileCompoment)
	class UStaticMeshComponent* TileActor;
	float ConstLocationValue = 0.0f;

	AFinalProjectGameMode* hGameMode = Cast<AFinalProjectGameMode>(UGameplayStatics::GetGameMode(this));

};
