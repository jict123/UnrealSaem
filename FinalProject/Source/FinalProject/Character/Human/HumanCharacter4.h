// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/Human/HumanCharacter.h"
#include "HumanCharacter4.generated.h"

/**
*
*/
UCLASS()
class FINALPROJECT_API AHumanCharacter4 : public AHumanCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHumanCharacter4();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	AController* hController;

	/*bool bDeath = false;
	bool bAgro = false;
	bool bFirst = true;*/

	float death_time = 0.0f;

	AActor* AgroTarget;

	float GetHp() { return hHp; }

	void SetNum(int *num) { nNum = *num; }
	void SetAgro(bool *Agro) { bAgro = *Agro; }
	void SetHp(float *Hp) { hHp = *Hp; }
	void SetDeath(bool Death) { bDeath = Death; }

	/*UAnimSequence* WalkAnim;		//이동 애니메이션
	UAnimSequence* AttackAnim;		//공격 애니메이션*/

	/*UFUNCTION(BlueprintCallable, Category = "HumanState")
	bool IsAgro() const { return bAgro; }

	UFUNCTION(BlueprintCallable, Category = "HumanState")
	bool IsDeath() const { return bDeath; }*/


};
