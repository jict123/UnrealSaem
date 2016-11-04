// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "HumanBehaviorTree.h"
#include "Character/Human/HumanCharacter.h"
#include "Character/Animal/AnimalCharacter.h"
#include "Character/Human/HumanAIController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FinalProjectGameMode.h"
#include "Building/Human/HumanBuilding.h"
#include "Building/Animal/AnimalBuilding.h"
bool hCheckHp::run()
{
	AHumanAIController* humancontroller = Cast<AHumanAIController>(Controller);
	AHumanCharacter* human = Cast<AHumanCharacter>(humancontroller->GetPawn());
	
	if (human->GetHp() <= 0.0f) {
		human->SetDeath(true);
		return false;
	}
	
	return true;
}


bool hCheckAgro::run()
{
	AHumanAIController* humancontroller = Cast<AHumanAIController>(Controller);
	AHumanCharacter* human = Cast<AHumanCharacter>(humancontroller->GetPawn());
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Destructible));
	TArray<AActor*> A;
	TArray<AActor*> B;
	TArray<AActor*> ActorsToIgnore;
	UGameplayStatics::GetAllActorsOfClass(GWorld->GetWorld(), AHumanCharacter::StaticClass(), A);
	UGameplayStatics::GetAllActorsOfClass(GWorld->GetWorld(), AHumanBuilding::StaticClass(), B);
	ActorsToIgnore.Append(A);
	ActorsToIgnore.Append(B);
	FHitResult OutHits;

	bool Agro = UKismetSystemLibrary::SphereTraceSingleForObjects(GWorld->GetWorld(), human->GetActorLocation(), human->GetActorLocation() + FVector(0.0f, 0.0f, 10.0f), 300.0f, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);

	human->SetAgroTarget(OutHits.GetActor());
	if (Agro == false) {
		human->SetAgro(&Agro);
		human->SetAttack(&Agro);
	}

	return Agro;
}


bool hMoveTask::run()
{
	AHumanAIController* humancontroller = Cast<AHumanAIController>(Controller);
	AHumanCharacter* human = Cast<AHumanCharacter>(humancontroller->GetPawn());

	humancontroller->MoveToActor(Target);

	return true;
}

bool hMoveTargetTask::run()
{
	AHumanAIController* humancontroller = Cast<AHumanAIController>(Controller);
	AHumanCharacter* human = Cast<AHumanCharacter>(humancontroller->GetPawn());
	static bool attack;
	if (human->GetTarget()->IsA(AAnimalCharacter::StaticClass())) {
		AAnimalCharacter* animal = Cast<AAnimalCharacter>(human->GetTarget());
		humancontroller->MoveToActor(animal, (Range-150.0f));
		if (humancontroller->MoveToActor(animal, (Range-150.0f)) == EPathFollowingRequestResult::Type::AlreadyAtGoal) {
			attack = true;
			human->SetAttack(&attack);
		}
	}
	else if (human->GetTarget()->IsA(AAnimalBuilding::StaticClass())) {
		AAnimalBuilding* animalBuilding = Cast<AAnimalBuilding>(human->GetTarget());
		humancontroller->MoveToActor(animalBuilding, (Range));
		if (humancontroller->MoveToActor(animalBuilding, (Range)) == EPathFollowingRequestResult::Type::AlreadyAtGoal) {
			attack = true;
			human->SetAttack(&attack);
		}
	}
	return true;

}

bool hAttackTask::run()
{
	AHumanAIController* humancontroller = Cast<AHumanAIController>(Controller);
	AHumanCharacter* human = Cast<AHumanCharacter>(humancontroller->GetPawn());
	static bool agro;
	if (human->GetAttack() == true) {
		agro = true;
		human->SetAgro(&agro);
		if (human->GetDamage() == true) {
			if (human->GetTarget()->IsA(AAnimalCharacter::StaticClass())) {
				AAnimalCharacter* animal = Cast<AAnimalCharacter>(human->GetTarget());
				float hp = animal->GetHp() - fDamage;
				animal->SetHp(&hp);
			}
			else if (human->GetTarget()->IsA(AAnimalBuilding::StaticClass())) {
				AAnimalBuilding* animalBuilding = Cast<AAnimalBuilding>(human->GetTarget());
				float hp = animalBuilding->GetHp() - fDamage;
				animalBuilding->SetHp(&hp);
			}
			human->SetDamage(&bF);
		}
	}

	return true;
}