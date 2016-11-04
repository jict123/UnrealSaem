// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/Human/HumanCharacter.h"
#include "HumanCharacter2.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AHumanCharacter2 : public AHumanCharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AHumanCharacter2();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	AController* hController;

	float death_time = 0.0f;

	AActor* AgroTarget;

	float GetHp() { return hHp; }

	void SetNum(int *num) { nNum = *num; }
	void SetAgro(bool *Agro) { bAgro = *Agro; }
	void SetHp(float *Hp) { hHp = *Hp; }
	void SetDeath(bool Death) { bDeath = Death; }
	
	
};
