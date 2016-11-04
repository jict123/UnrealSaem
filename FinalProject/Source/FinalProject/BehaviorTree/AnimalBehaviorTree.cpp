// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "AnimalBehaviorTree.h"
#include "Character/Animal/AnimalCharacter.h"
#include "Character/Human/HumanCharacter.h"
#include "Character/Human/HumanAIController.h"
#include "Character/Animal/AnimalAIController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FinalProjectGameMode.h"
#include "Building/Human/HumanBuilding.h"
#include "Building/Animal/AnimalBuilding.h"

bool aCheckHp::run()
{
	AAnimalAIController* animalcontroller = Cast<AAnimalAIController>(Controller);
	AAnimalCharacter* animal = Cast<AAnimalCharacter>(animalcontroller->GetPawn());

	if (animal->GetHp() <= 0.0f){
		animal->SetDeath(true);
		return false;
	}


	return true;
}


bool aCheckAgro::run()
{
	AAnimalAIController* Animalcontroller = Cast<AAnimalAIController>(Controller);
	AAnimalCharacter* Animal = Cast<AAnimalCharacter>(Animalcontroller->GetPawn());

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Destructible));
	TArray<AActor*> A;
	TArray<AActor*> B;
	TArray<AActor*> ActorsToIgnore;
	UGameplayStatics::GetAllActorsOfClass(GWorld->GetWorld(), AAnimalCharacter::StaticClass(), A);
	UGameplayStatics::GetAllActorsOfClass(GWorld->GetWorld(), AAnimalBuilding::StaticClass(), B);
	ActorsToIgnore.Append(A);
	ActorsToIgnore.Append(B);
	FHitResult hit;
	
	bool Agro = UKismetSystemLibrary::SphereTraceSingleForObjects(GWorld->GetWorld(), Animal->GetActorLocation(), Animal->GetActorLocation() + FVector(0.0f, 0.0f, 10.0f), 300.0f, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, hit, true);

	Animal->SetAgroTarget(hit.GetActor());
	if (Agro == false) {
		Animal->SetAgro(&Agro);
		Animal->SetAttack(&Agro);
	}

	return Agro;

}


bool aMoveTask::run()
{
	/*if (bRe == true)
		return false;*/
	AAnimalAIController* Animalcontroller = Cast<AAnimalAIController>(Controller);
	AAnimalCharacter* Animal = Cast<AAnimalCharacter>(Animalcontroller->GetPawn());

	int n;
	Animalcontroller->MoveToActor(Target);
	if (((Animal->GetActorLocation().X <= Target->GetActorLocation().X + 75.0f) && (Animal->GetActorLocation().X >= Target->GetActorLocation().X - 75.0f)) && ((Animal->GetActorLocation().Y <= Target->GetActorLocation().Y + 75.0f) && (Animal->GetActorLocation().Y >= Target->GetActorLocation().Y - 75.0f))) {
		n = Animal->GetNum() + 1;
		Animal->SetNum(&n);
	}

	return true;
}

bool aMoveTask2::run()
{
	if (bRe == false)
		return false;
	AAnimalAIController* Animalcontroller = Cast<AAnimalAIController>(Controller);
	AAnimalCharacter* Animal = Cast<AAnimalCharacter>(Animalcontroller->GetPawn());

	int n;

	Animalcontroller->MoveToActor(Target);
	Animalcontroller->MoveToActor(Target);
	if (((Animal->GetActorLocation().X <= Target->GetActorLocation().X + 75.0f) && (Animal->GetActorLocation().X >= Target->GetActorLocation().X - 75.0f)) && ((Animal->GetActorLocation().Y <= Target->GetActorLocation().Y + 75.0f) && (Animal->GetActorLocation().Y >= Target->GetActorLocation().Y - 75.0f))) {
		n = Animal->GetNum() - 1;
		Animal->SetNum(&n);
	}

	return true;
}

bool aMoveTargetTask::run()
{
	AAnimalAIController* Animalcontroller = Cast<AAnimalAIController>(Controller);
	AAnimalCharacter* Animal = Cast<AAnimalCharacter>(Animalcontroller->GetPawn());

	static bool attack;
	if (Animal->GetTarget()->IsA(AHumanCharacter::StaticClass())) {
		AHumanCharacter* human = Cast<AHumanCharacter>(Animal->GetTarget());
		Animalcontroller->MoveToActor(human, (Range-150.0f));
		if (Animalcontroller->MoveToActor(human, (Range-150.0f)) == EPathFollowingRequestResult::Type::AlreadyAtGoal) {
			attack = true;
			Animal->SetAttack(&attack);
		}
	}
	else if (Animal->GetTarget()->IsA(AHumanBuilding::StaticClass())) {
		AHumanBuilding* animalBuilding = Cast<AHumanBuilding>(Animal->GetTarget());
		Animalcontroller->MoveToActor(animalBuilding, (Range));
		if (Animalcontroller->MoveToActor(animalBuilding, (Range)) == EPathFollowingRequestResult::Type::AlreadyAtGoal) {
			attack = true;
			Animal->SetAttack(&attack);
		}
	}
	return true;
}

bool aAttackTask::run()
{
	AAnimalAIController* Animalcontroller = Cast<AAnimalAIController>(Controller);
	AAnimalCharacter* Animal = Cast<AAnimalCharacter>(Animalcontroller->GetPawn());
	static bool agro;
	if (Animal->GetAttack() == true) {
		agro = true;
		Animal->SetAgro(&agro);
		if (Animal->GetDamage() == true) {
			if (Animal->GetTarget()->IsA(AHumanCharacter::StaticClass())) {
				AHumanCharacter* human = Cast<AHumanCharacter>(Animal->GetTarget());
				float hp = human->GetHp() - fDamage;
				human->SetHp(&hp);
			}
			else if (Animal->GetTarget()->IsA(AHumanBuilding::StaticClass())) {
				AHumanBuilding* humanBuilding = Cast<AHumanBuilding>(Animal->GetTarget());
				float hp = humanBuilding->GetHp() - fDamage;
				humanBuilding->SetHp(&hp);
			}
			Animal->SetDamage(&bF);
		}
	}

	return true;
}