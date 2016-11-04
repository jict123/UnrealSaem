// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FinalProjectGameMode.h"
#include "GameFramework/Character.h"
#include "AnimalCharacter.generated.h"

UCLASS()
class FINALPROJECT_API AAnimalCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AAnimalCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	AController* hController;

	AActor* AgroTarget;

	float GetHp() { return aHp; }
	AActor* GetTarget() { return AgroTarget; }
	bool GetAgro() { return bAgro; }
	void SetNum(int *num) { nNum = *num; }
	void SetAgro(bool *Agro) { bAgro = *Agro; }
	void SetHp(float *Hp) { aHp = *Hp; }
	void SetDeath(bool Death) { bDeath = Death; }
	void SetAgroTarget(AActor* Target) { AgroTarget = Target; }
	int GetNum() { return nNum; }
	void SetAttack(bool *attack) { bAttack = *attack; }
	bool GetAttack() { return bAttack; }
	void SetDamage(bool *damage) { bDamage = *damage; }
	bool GetDamage() { return bDamage; }

	UFUNCTION(BlueprintCallable, Category = "HumanState")
	bool IsAgro() const { return bAgro; }

	UFUNCTION(BlueprintCallable, Category = "HumanState")
	bool IsDeath() const { return bDeath; }


protected:
	float ConstLocationValue = 0.0f;
	float aHp;
	int nNum;
	bool bDeath = false;
	bool bAgro = false;
	bool bFirst = true;
	bool bAttack = false;
	bool bDamage = false;
	bool bRe;
	float death_time = 0.0f;
	float Attack_time = 0;

	AFinalProjectGameMode* aGameMode = Cast<AFinalProjectGameMode>(UGameplayStatics::GetGameMode(this));
	UAnimSequence* msIdleAnim;


};
