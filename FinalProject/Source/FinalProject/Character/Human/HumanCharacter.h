// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FinalProjectGameMode.h"
#include "BehaviorTree/HumanBehaviorTree.h"
#include "GameFramework/Character.h"
#include "HumanCharacter.generated.h"

UCLASS()
class FINALPROJECT_API AHumanCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHumanCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual void PostInitializeComponents() override;
	AController* hController;

	

	AActor* AgroTarget;

	float GetHp() { return hHp; }
	AActor* GetTarget() { return AgroTarget; }
	bool GetAgro() { return bAgro; }
	void SetNum(int *num) { nNum = *num; }
	void SetAgro(bool *Agro) { bAgro = *Agro; }
	void SetHp(float *Hp) { hHp = *Hp; }
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
	float hHp;
	int nNum;
	bool bDeath = false;
	bool bAgro = false;
	bool bFirst = true;
	bool bAttack = false;
	bool bDamage = false;
	bool bRe;
	float death_time = 0.0f;
	float Attack_time = 0;
	AFinalProjectGameMode* hGameMode = Cast<AFinalProjectGameMode>(UGameplayStatics::GetGameMode(this));

	Sequence *root;
	Sequence *sequence1;
	Sequence *sequence2;
	Selector* selector;
	hCheckHp* checkhp;
	hCheckAgro* checkagro;
	hMoveTask* move;
	hMoveTargetTask* movetarget;
	hAttackTask* attack;
};
