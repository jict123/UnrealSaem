// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "AnimalAI.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "FinalProjectGameMode.h"
#include "FPSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Core/Public/Math/RandomStream.h"

#include "Building/Human/HumanBuilding.h"
#include "Building/Human/HumanBuilding_Create1.h"
#include "Building/Human/HumanBuilding_Create2.h"
#include "Building/Human/HumanBuilding_Create3.h"
#include "Building/Human/HumanBuilding_Defend.h"
#include "Building/Human/HumanBuilding_Resource.h"

#include "Building/Animal/AnimalBuilding.h"
#include "Building/Animal/AnimalBuilding_Create1.h"
#include "Building/Animal/AnimalBuilding_Create2.h"
#include "Building/Animal/AnimalBuilding_Create3.h"
#include "Building/Animal/AnimalBuilding_Defend.h"
#include "Building/Animal/AnimalBuilding_Resource.h"

#include "Character/Animal/AnimalCharacter.h"
#include "Character/Animal/AnimalCharacter1.h"
#include "Character/Animal/AnimalCharacter2.h"
#include "Character/Animal/AnimalCharacter3.h"
#include "Character/Animal/AnimalCharacter4.h"
#include "Character/Animal/AnimalCharacter5.h"

#include "Character/Human/HumanCharacter.h"
#include "Character/Human/HumanCharacter1.h"
#include "Character/Human/HumanCharacter2.h"
#include "Character/Human/HumanCharacter3.h"
#include "Character/Human/HumanCharacter4.h"
#include "Character/Human/HumanCharacter5.h"

// Sets default values
AAnimalAI::AAnimalAI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAnimalAI::BeginPlay()
{
	Super::BeginPlay();

	vSpawn.Add(FVector(200.0f, -1900.0f, 100.0f));
	vSpawn.Add(FVector(200.0f, -1300.0f, 100.0f));
	vSpawn.Add(FVector(800.0f, -1900.0f, 100.0f));
	vSpawn.Add(FVector(800.0f, -1300.0f, 100.0f));
	vSpawn.Add(FVector(1300.0f, -1900.0f, 100.0f));
	vSpawn.Add(FVector(1300.0f, -1300.0f, 100.0f));
	vSpawn.Add(FVector(1300.0f, -200.0f, 100.0f));
	vSpawn.Add(FVector(1300.0f, -800.0f, 100.0f));
	vSpawn.Add(FVector(1900.0f, -1900.0f, 100.0f));
	vSpawn.Add(FVector(1900.0f, -1300.0f, 100.0f));
	vSpawn.Add(FVector(1900.0f, -200.0f, 100.0f));
	vSpawn.Add(FVector(1900.0f, -800.0f, 100.0f));
	vSpawn.Add(FVector(2400.0f, -200.0f, 100.0f));
	vSpawn.Add(FVector(2400.0f, -800.0f, 100.0f));
	vSpawn.Add(FVector(3000.0f, -200.0f, 100.0f));
	vSpawn.Add(FVector(3000.0f, -800.0f, 100.0f));


	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Destructible));

	UGameplayStatics::GetAllActorsOfClass(GWorld->GetWorld(), AHumanCharacter::StaticClass(), A);
	UGameplayStatics::GetAllActorsOfClass(GWorld->GetWorld(), AHumanBuilding::StaticClass(), B);
	UGameplayStatics::GetAllActorsOfClass(GWorld->GetWorld(), AAnimalCharacter::StaticClass(), C);
	UGameplayStatics::GetAllActorsOfClass(GWorld->GetWorld(), AAnimalBuilding::StaticClass(), D);
	
	fPass = 0.0f;
	nDifficult = FMath::RandRange(1, 3);
	if (nDifficult == 1)
		fMana = 150.0f;
	else if (nDifficult == 2)
		fMana = 180.0f;
	else if (nDifficult == 3)
		fMana = 200.0f;
	fManaSecond = 0.0f;
	
}

// Called every frame
void AAnimalAI::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	InitScore();
	//CheckHuman();
	CheckAnimal();
	//ActionAI(DeltaTime);
	fManaSecond += DeltaTime;
	if (fManaSecond > 1.0f)
	{
		AIAction(DeltaTime, nDifficult);
		fMana += 5 * nAnimal_Resource;
		fManaSecond = 0.0f;
	}
	UE_LOG(LogClass, Log, TEXT("%f"), fMana);
}

void AAnimalAI::InitScore()
{
	fHuman_Score = 0.0f;
	fAnimal_Score = 0.0f;
	nAnimal1 = 0;
	nAnimal2 = 0;
	nAnimal3 = 0;
	nAnimal_Resource = 0;
	nAnimal_Defend = 0;

	nHumanUnit1 = 0;
	nHumanUnit2 = 0;
	nHumanUnit3 = 0;
	nHumanUnit4 = 0;
	nHumanUnit5 = 0;


	nAnimalUnit1 = 0;
	nAnimalUnit2 = 0;
	nAnimalUnit3 = 0;
	nAnimalUnit4 = 0;
	nAnimalUnit5 = 0;

	vCreate1.Reset();
	vCreate2.Reset();

}

void AAnimalAI::CheckHuman()
{
	/*TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Append(C);
	ActorsToIgnore.Append(D);
	
	bool Agro = UKismetSystemLibrary::BoxTraceMultiForObjects(GWorld->GetWorld(), FVector(2200.0f, -2200.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(2500.0f, 2500.0f, 500.0f), FRotator(0.0f, 0.0f, 0.0f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);

	for (int i = 0; i < OutHits.Num(); i++)
	{
		if (OutHits[i].GetActor()->IsA(AHumanBuilding_Create1::StaticClass())) {
			fHuman_Score += 10.0f;
		}
		else if (OutHits[i].GetActor()->IsA(AHumanBuilding_Create2::StaticClass())) {
			fHuman_Score += 15.0f;
		}
		else if (OutHits[i].GetActor()->IsA(AHumanBuilding_Create3::StaticClass())) {
			fHuman_Score += 20.0f;
		}
		else if (OutHits[i].GetActor()->IsA(AHumanBuilding_Defend::StaticClass())) {
			fHuman_Score += 10.0f;
		}
		else if (OutHits[i].GetActor()->IsA(AHumanBuilding_Resource::StaticClass())) {
			fHuman_Score += 10.0f;
		}
		else if (OutHits[i].GetActor()->IsA(AHumanCharacter1::StaticClass())) {
			fHuman_Score += 2.5f;
			nHumanUnit1 += 1;
		}
		else if (OutHits[i].GetActor()->IsA(AHumanCharacter2::StaticClass())) {
			fHuman_Score += (5.0f / 24.0f);
			nHumanUnit2 += 1;
		}
		else if (OutHits[i].GetActor()->IsA(AHumanCharacter3::StaticClass())) {
			fHuman_Score += (7.5f / 24.0f);
			nHumanUnit3 += 1;
		}
		else if (OutHits[i].GetActor()->IsA(AHumanCharacter4::StaticClass())) {
			fHuman_Score += (10.0f/23.0f);
			nHumanUnit4 += 1;
		}
		else if (OutHits[i].GetActor()->IsA(AHumanCharacter5::StaticClass())) {
			fHuman_Score += (20.0f/26.0f);
			nHumanUnit5 += 1;
		}
	}
	fHuman_Score += fPass;*/
}


void AAnimalAI::CheckAnimal()
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Append(A);
	ActorsToIgnore.Append(B);
	
	bool Agro = UKismetSystemLibrary::BoxTraceMultiForObjects(GWorld->GetWorld(), FVector(2200.0f, -2200.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(2500.0f, 2500.0f, 500.0f), FRotator(0.0f, 0.0f, 0.0f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);

	for (int i = 0; i < OutHits.Num(); i++)
	{
		if (OutHits[i].GetActor()->IsA(AAnimalBuilding_Create1::StaticClass())) {
			fAnimal_Score += 10.0f;
			nAnimal1 += 1;
			AActor* HitActor = OutHits[i].GetActor();
			vCreate1.Add(HitActor->GetActorLocation());
		}
		else if (OutHits[i].GetActor()->IsA(AAnimalBuilding_Create2::StaticClass())) {
			fAnimal_Score += 15.0f;
			nAnimal2 += 1;
			AActor* HitActor = OutHits[i].GetActor();
			vCreate2.Add(HitActor->GetActorLocation());
		}
		else if (OutHits[i].GetActor()->IsA(AAnimalBuilding_Create3::StaticClass())) {
			fAnimal_Score += 20.0f;
			nAnimal3 += 1;
		}
		else if (OutHits[i].GetActor()->IsA(AAnimalBuilding_Defend::StaticClass())) {
			fAnimal_Score += 10.0f;
			nAnimal_Defend += 1;
		}
		else if (OutHits[i].GetActor()->IsA(AAnimalBuilding_Resource::StaticClass())) {
			fAnimal_Score += 10.0f;
			nAnimal_Resource += 1;
		}
		else if (OutHits[i].GetActor()->IsA(AAnimalCharacter1::StaticClass())) {
			fAnimal_Score += 2.5f;
			nAnimalUnit1 += 1;
		}
		else if (OutHits[i].GetActor()->IsA(AAnimalCharacter2::StaticClass())) {
			fAnimal_Score += 5.0f;
			nAnimalUnit2 += 1;
		}
		else if (OutHits[i].GetActor()->IsA(AAnimalCharacter3::StaticClass())) {
			fAnimal_Score += 7.5f;
			nAnimalUnit3 += 1;
		}
		else if (OutHits[i].GetActor()->IsA(AAnimalCharacter4::StaticClass())) {
			fAnimal_Score += 10.0f;
			nAnimalUnit4 += 1;
		}
		else if (OutHits[i].GetActor()->IsA(AAnimalCharacter5::StaticClass())) {
			fAnimal_Score += 20.0f;
			nAnimalUnit5 += 1;
		}
	}
}

void AAnimalAI::ActionAI(float fDeltatime)
{
	TArray<AActor*> ActorsToIgnore;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	fPass += fDeltatime*0.3f;
	if (fHuman_Score > fAnimal_Score) {
		float fScoreGap = fHuman_Score - fAnimal_Score;
		if (fScoreGap > 0 && fScoreGap <= 2.5) {
			int nSelector = FMath::RandRange(1, 2);
			if (nAnimal1 >= 1 && (nHumanUnit1 >= 1 || nHumanUnit2 >= 1 || nHumanUnit3 >= 1 || nHumanUnit4 >= 1) && nAnimalUnit1 < 1 && nSelector == 1 && fMana > 10.0f) {
				int num = FMath::RandRange(0, vCreate1.Num() - 1);
				FVector vSpawnVector = SpawnLocation(vCreate1[num]);
				UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter1::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 10.0f;
				fPass = 0.0f;
			}
			else
			{
			}
		}
		else if (fScoreGap > 2.5 && fScoreGap <= 5) {
			int nSelector = FMath::RandRange(1, 3);
			if (nAnimal1 >= 1 && (nHumanUnit1 >= 1 || nHumanUnit2 >= 1 || nHumanUnit3 >= 1 || nHumanUnit4 >= 1) && nAnimalUnit1 < 2 && nSelector == 1 && fMana > 10.0f) {
				int num = FMath::RandRange(0, vCreate1.Num() - 1);
				FVector vSpawnVector = SpawnLocation(vCreate1[num]);
				UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter1::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 10.0f;
				fPass = 0.0f;
			}
			else if (nAnimal1 >= 1 && (nHumanUnit1 >= 1 || nHumanUnit2 >= 1 || nHumanUnit3 >= 1 || nHumanUnit4 >= 1) && nAnimalUnit2 < 2 && nSelector == 2 && fMana > 15.0f) {
				int num = FMath::RandRange(0, vCreate1.Num() - 1);
				FVector vSpawnVector = SpawnLocation(vCreate1[num]);
				UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter2::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 15.0f;
				fPass = 0.0f;
			}
			else {
			}
		}
		else if (fScoreGap > 5 && fScoreGap < 10) {
			int nSelector = FMath::RandRange(1, 4);
			if (nAnimal1 >= 1 && (nHumanUnit1 >= 1 || nHumanUnit2 >= 1 || nHumanUnit3 >= 1 || nHumanUnit4 >= 1) && nAnimalUnit1 < 3 && nSelector == 1 && fMana > 10.0f) {
				int num = FMath::RandRange(0, vCreate1.Num() - 1);
				FVector vSpawnVector = SpawnLocation(vCreate1[num]);
				UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter1::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 10.0f;
				fPass = 0.0f;
			}
			else if (nAnimal1 >= 1 && (nHumanUnit1 >= 1 || nHumanUnit2 >= 1 || nHumanUnit3 >= 1 || nHumanUnit4 >= 1) && nAnimalUnit2 < 3 && nSelector == 2 && fMana > 15.0f) {
				int num = FMath::RandRange(0, vCreate1.Num() - 1);
				FVector vSpawnVector = SpawnLocation(vCreate1[num]);
				UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter2::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 15.0f;
				fPass = 0.0f;
			}
			else if (nAnimal2 >= 1 && (nHumanUnit1 >= 1 || nHumanUnit2 >= 1 || nHumanUnit3 >= 1 || nHumanUnit4 >= 1) && nAnimalUnit3 < 3 && nSelector == 3 && fMana > 20.0f) {
				int num = FMath::RandRange(0, vCreate2.Num() - 1);
				FVector vSpawnVector = SpawnLocation(vCreate2[num]);
				UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter3::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 20.0f;
				fPass = 0.0f;
			}
			else {
			}
		}
	
		else if (fScoreGap >= 10 && fScoreGap <= 20) {
			int nSelector = FMath::RandRange(1, 5);

			if (nAnimal_Resource == 1 && fMana > 50.0f) {
				int num;
				for (int n = 0; n < vSpawn.Num(); n++) {
					num = FMath::RandRange(0, vSpawn.Num() - 1);

					bool Agro = UKismetSystemLibrary::BoxTraceMultiForObjects(GWorld->GetWorld(), vSpawn[num], FVector(0.0f, 0.0f, 0.0f), FVector(200.0f, 200.0f, 300.0f), FRotator(0.0f, 0.0f, 0.0f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);
					if (Agro == false)
						break;
				}
				GWorld->SpawnActor<AAnimalBuilding_Resource>(AAnimalBuilding_Resource::StaticClass(), vSpawn[num], FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 50.0f;
				fPass = 0.0f;
			}
			else if (nAnimal1 == 0 && fMana > 70.0f) {
				int num;
				for (int n = 0; n < vSpawn.Num(); n++) {
					num = FMath::RandRange(0, vSpawn.Num() - 1);

					bool Agro = UKismetSystemLibrary::BoxTraceMultiForObjects(GWorld->GetWorld(), vSpawn[num], FVector(0.0f, 0.0f, 0.0f), FVector(200.0f, 200.0f, 300.0f), FRotator(0.0f, 0.0f, 0.0f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);
					if (Agro == false)
						break;
				}
				GWorld->SpawnActor<AAnimalBuilding_Create1>(AAnimalBuilding_Create1::StaticClass(), vSpawn[num], FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 70.0f;
				fPass = 0.0f;
			}
			else if (nAnimal2 == 0 && fMana > 100.0f) {
				int num;
				for (int n = 0; n < vSpawn.Num(); n++) {
					num = FMath::RandRange(0, vSpawn.Num() - 1);

					bool Agro = UKismetSystemLibrary::BoxTraceMultiForObjects(GWorld->GetWorld(), vSpawn[num], FVector(0.0f, 0.0f, 0.0f), FVector(200.0f, 200.0f, 300.0f), FRotator(0.0f, 0.0f, 0.0f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);
					if (Agro == false)
						break;
				}
				GWorld->SpawnActor<AAnimalBuilding_Create2>(AAnimalBuilding_Create2::StaticClass(), vSpawn[num], FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 100.0f;
				fPass = 0.0f;
			}

			else if (nAnimal1 >= 1 && (nHumanUnit1 >= 1 || nHumanUnit2 >= 1 || nHumanUnit3 >= 1 || nHumanUnit4 >= 1) && nAnimalUnit1 < 4 && nSelector == 1 && fMana > 10.0f) {
				int num = FMath::RandRange(0, vCreate1.Num() - 1);
				FVector vSpawnVector = SpawnLocation(vCreate1[num]);
				UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter1::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 10.0f;
				fPass = 0.0f;
			}
			else if (nAnimal1 >= 1 && (nHumanUnit1 >= 1 || nHumanUnit2 >= 1 || nHumanUnit3 >= 1 || nHumanUnit4 >= 1) && nAnimalUnit2 < 4 && nSelector == 2 && fMana > 15.0f) {
				int num = FMath::RandRange(0, vCreate1.Num() - 1);
				FVector vSpawnVector = SpawnLocation(vCreate1[num]);
				UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter2::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 15.0f;
				fPass = 0.0f;
			}
			else if (nAnimal2 >= 1 && (nHumanUnit1 >= 1 || nHumanUnit2 >= 1 || nHumanUnit3 >= 1 || nHumanUnit4 >= 1) && nAnimalUnit3 < 4 && nSelector == 3 && fMana > 20.0f) {
				int num = FMath::RandRange(0, vCreate2.Num() - 1);
				FVector vSpawnVector = SpawnLocation(vCreate2[num]);
				UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter3::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 20.0f;
				fPass = 0.0f;
			}
			else if (nAnimal2 >= 1 && (nHumanUnit1 >= 1 || nHumanUnit2 >= 1 || nHumanUnit3 >= 1 || nHumanUnit4 >= 1) && nAnimalUnit4 < 4 && nSelector == 4 && fMana > 25.0f) {
				int num = FMath::RandRange(0, vCreate2.Num() - 1);
				FVector vSpawnVector = SpawnLocation(vCreate2[num]);
				UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter4::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 25.0f;
				fPass = 0.0f;
			}
			else {
			}
		}

		else if (fScoreGap > 20) {
			int nSelector = FMath::RandRange(1, 5);
			if (nAnimal3 == 0) {
				int num;
				for (int n = 0; n < vSpawn.Num(); n++) {
					num = FMath::RandRange(0, vSpawn.Num() - 1);

					bool Agro = UKismetSystemLibrary::BoxTraceMultiForObjects(GWorld->GetWorld(), vSpawn[num], FVector(0.0f, 0.0f, 0.0f), FVector(200.0f, 200.0f, 300.0f), FRotator(0.0f, 0.0f, 0.0f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);
					if (Agro == false)
						break;
				}
				GWorld->SpawnActor<AAnimalBuilding_Create3>(AAnimalBuilding_Create3::StaticClass(), vSpawn[num], FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 25.0f;
				fPass = 0.0f;
			}
			else if (nAnimal_Resource <= 2 && fMana > 50.0f) {
				int num;
				for (int n = 0; n < vSpawn.Num(); n++) {
					num = FMath::RandRange(0, vSpawn.Num() - 1);

					bool Agro = UKismetSystemLibrary::BoxTraceMultiForObjects(GWorld->GetWorld(), vSpawn[num], FVector(0.0f, 0.0f, 0.0f), FVector(200.0f, 200.0f, 300.0f), FRotator(0.0f, 0.0f, 0.0f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);
					if (Agro == false)
						break;
				}
				GWorld->SpawnActor<AAnimalBuilding_Resource>(AAnimalBuilding_Resource::StaticClass(), vSpawn[num], FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 50.0f;
				fPass = 0.0f;
			}
			else if (nAnimal1 <= 1 && fMana > 70.0f) {
				int num;
				for (int n = 0; n < vSpawn.Num(); n++) {
					num = FMath::RandRange(0, vSpawn.Num() - 1);

					bool Agro = UKismetSystemLibrary::BoxTraceMultiForObjects(GWorld->GetWorld(), vSpawn[num], FVector(0.0f, 0.0f, 0.0f), FVector(200.0f, 200.0f, 300.0f), FRotator(0.0f, 0.0f, 0.0f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);
					if (Agro == false)
						break;
				}
				GWorld->SpawnActor<AAnimalBuilding_Create1>(AAnimalBuilding_Create1::StaticClass(), vSpawn[num], FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 70.0f;
				fPass = 0.0f;
			}
			else if (nAnimal2 <= 1 && fMana > 100.0f) {
				int num;
				for (int n = 0; n < vSpawn.Num(); n++) {
					num = FMath::RandRange(0, vSpawn.Num() - 1);

					bool Agro = UKismetSystemLibrary::BoxTraceMultiForObjects(GWorld->GetWorld(), vSpawn[num], FVector(0.0f, 0.0f, 0.0f), FVector(200.0f, 200.0f, 300.0f), FRotator(0.0f, 0.0f, 0.0f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);
					if (Agro == false)
						break;
				}
				GWorld->SpawnActor<AAnimalBuilding_Create2>(AAnimalBuilding_Create2::StaticClass(), vSpawn[num], FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 100.0f;
				fPass = 0.0f;
			}
			else if (nAnimal1 >= 1 && (nHumanUnit1 >= 1 || nHumanUnit2 >= 1 || nHumanUnit3 >= 1 || nHumanUnit4 >= 1) && nAnimalUnit1 < 5 && nSelector == 1 && fMana > 10.0f) {
				int num = FMath::RandRange(0, vCreate1.Num() - 1);
				FVector vSpawnVector = SpawnLocation(vCreate1[num]);
				UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter1::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 10.0f;
				fPass = 0.0f;
			}
			else if (nAnimal1 >= 1 && (nHumanUnit1 >= 1 || nHumanUnit2 >= 1 || nHumanUnit3 >= 1 || nHumanUnit4 >= 1) && nAnimalUnit2 < 5 && nSelector == 2 && fMana > 15.0f) {
				int num = FMath::RandRange(0, vCreate1.Num() - 1);
				FVector vSpawnVector = SpawnLocation(vCreate1[num]);
				UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter2::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 15.0f;
				fPass = 0.0f;;
			}
			else if (nAnimal2 >= 1 && (nHumanUnit1 >= 1 || nHumanUnit2 >= 1 || nHumanUnit3 >= 1 || nHumanUnit4 >= 1) && nAnimalUnit3 < 5 && nSelector == 3 && fMana > 20.0f) {
				int num = FMath::RandRange(0, vCreate2.Num() - 1);
				FVector vSpawnVector = SpawnLocation(vCreate2[num]);
				UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter3::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 20.0f;
				fPass = 0.0f;
			}
			else if (nAnimal2 >= 1 && (nHumanUnit1 >= 1 || nHumanUnit2 >= 1 || nHumanUnit3 >= 1 || nHumanUnit4 >= 1) && nAnimalUnit4 < 5 && nSelector == 4 && fMana > 25.0f) {
				int num = FMath::RandRange(0, vCreate2.Num() - 1);
				FVector vSpawnVector = SpawnLocation(vCreate2[num]);
				UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter4::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
				fMana -= 25.0f;
				fPass = 0.0f;
			}
			else {
			}
			
		}

	}
}

void AAnimalAI::AIAction(float fTime,int Difficult)
{
	TArray<AActor*> ActorsToIgnore;
	int SelectAction = FMath::RandRange(0, 5);
	if (Difficult == 1) {
		if (nAnimal1 == 0 && fMana > 70.0f) {
			int num;
			for (int n = 0; n < vSpawn.Num(); n++) {
				num = FMath::RandRange(0, vSpawn.Num() - 1);

				bool Agro = UKismetSystemLibrary::BoxTraceMultiForObjects(GWorld->GetWorld(), vSpawn[num], FVector(0.0f, 0.0f, 0.0f), FVector(200.0f, 200.0f, 300.0f), FRotator(0.0f, 0.0f, 0.0f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);
				if (Agro == false)
					break;
			}
			GWorld->SpawnActor<AAnimalBuilding_Create1>(AAnimalBuilding_Create1::StaticClass(), vSpawn[num], FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 70.0f;
		}
		else if (nAnimal_Resource <= 1 && fMana > 50.0f && SelectAction == 0) {
			int num;
			for (int n = 0; n < vSpawn.Num(); n++) {
				num = FMath::RandRange(0, vSpawn.Num() - 1);

				bool Agro = UKismetSystemLibrary::BoxTraceMultiForObjects(GWorld->GetWorld(), vSpawn[num], FVector(0.0f, 0.0f, 0.0f), FVector(200.0f, 200.0f, 300.0f), FRotator(0.0f, 0.0f, 0.0f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);
				if (Agro == false)
					break;
			}
			GWorld->SpawnActor<AAnimalBuilding_Resource>(AAnimalBuilding_Resource::StaticClass(), vSpawn[num], FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 50.0f;
		}
		else if (nAnimal1 > 0 && fMana > 15.0f && SelectAction == 1) {
			int num = FMath::RandRange(0, vCreate1.Num() - 1);
			FVector vSpawnVector = SpawnLocation(vCreate1[num]);
			UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter1::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 15.0f;
		}
		else if (nAnimal1 > 0 && fMana > 20.0f && SelectAction == 2) {
			int num = FMath::RandRange(0, vCreate1.Num() - 1);
			FVector vSpawnVector = SpawnLocation(vCreate1[num]);
			UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter2::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 20.0f;
		}
		else if (nAnimal2 == 0 && fMana > 100.0f && SelectAction == 5) {
			int num;
			for (int n = 0; n < vSpawn.Num(); n++) {
				num = FMath::RandRange(0, vSpawn.Num() - 1);

				bool Agro = UKismetSystemLibrary::BoxTraceMultiForObjects(GWorld->GetWorld(), vSpawn[num], FVector(0.0f, 0.0f, 0.0f), FVector(200.0f, 200.0f, 300.0f), FRotator(0.0f, 0.0f, 0.0f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);
				if (Agro == false)
					break;
			}
			GWorld->SpawnActor<AAnimalBuilding_Create2>(AAnimalBuilding_Create2::StaticClass(), vSpawn[num], FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 100.0f;
		}
		else if (nAnimal2 > 0 && fMana > 30.0f && SelectAction == 3) {
			int num = FMath::RandRange(0, vCreate2.Num() - 1);
			FVector vSpawnVector = SpawnLocation(vCreate2[num]);
			UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter3::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 30.0f;
		}
		else if (nAnimal2 > 0 && fMana > 35.0f && SelectAction == 4) {
			int num = FMath::RandRange(0, vCreate2.Num() - 1);
			FVector vSpawnVector = SpawnLocation(vCreate2[num]);
			UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter4::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 35.0f;
		}
	}
	else if (Difficult == 2) {
		if (nAnimal1 == 0 && fMana > 65.0f) {
			int num;
			for (int n = 0; n < vSpawn.Num(); n++) {
				num = FMath::RandRange(0, vSpawn.Num() - 1);

				bool Agro = UKismetSystemLibrary::BoxTraceMultiForObjects(GWorld->GetWorld(), vSpawn[num], FVector(0.0f, 0.0f, 0.0f), FVector(200.0f, 200.0f, 300.0f), FRotator(0.0f, 0.0f, 0.0f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);
				if (Agro == false)
					break;
			}
			GWorld->SpawnActor<AAnimalBuilding_Create1>(AAnimalBuilding_Create1::StaticClass(), vSpawn[num], FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 65.0f;
		}
		else if (nAnimal_Resource <= 1 && fMana > 50.0f && SelectAction == 0) {
			int num;
			for (int n = 0; n < vSpawn.Num(); n++) {
				num = FMath::RandRange(0, vSpawn.Num() - 1);

				bool Agro = UKismetSystemLibrary::BoxTraceMultiForObjects(GWorld->GetWorld(), vSpawn[num], FVector(0.0f, 0.0f, 0.0f), FVector(200.0f, 200.0f, 300.0f), FRotator(0.0f, 0.0f, 0.0f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);
				if (Agro == false)
					break;
			}
			GWorld->SpawnActor<AAnimalBuilding_Resource>(AAnimalBuilding_Resource::StaticClass(), vSpawn[num], FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 50.0f;
		}
		else if (nAnimal1 > 0 && fMana > 12.0f && SelectAction == 1) {
			int num = FMath::RandRange(0, vCreate1.Num() - 1);
			FVector vSpawnVector = SpawnLocation(vCreate1[num]);
			UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter1::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 12.0f;
		}
		else if (nAnimal1 > 0 && fMana > 18.0f && SelectAction == 2) {
			int num = FMath::RandRange(0, vCreate1.Num() - 1);
			FVector vSpawnVector = SpawnLocation(vCreate1[num]);
			UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter2::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 18.0f;
		}
		else if (nAnimal2 == 0 && fMana > 90.0f && SelectAction == 5) {
			int num;
			for (int n = 0; n < vSpawn.Num(); n++) {
				num = FMath::RandRange(0, vSpawn.Num() - 1);

				bool Agro = UKismetSystemLibrary::BoxTraceMultiForObjects(GWorld->GetWorld(), vSpawn[num], FVector(0.0f, 0.0f, 0.0f), FVector(200.0f, 200.0f, 300.0f), FRotator(0.0f, 0.0f, 0.0f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);
				if (Agro == false)
					break;
			}
			GWorld->SpawnActor<AAnimalBuilding_Create2>(AAnimalBuilding_Create2::StaticClass(), vSpawn[num], FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 90.0f;
		}
		else if (nAnimal2 > 0 && fMana > 28.0f && SelectAction == 3) {
			int num = FMath::RandRange(0, vCreate2.Num() - 1);
			FVector vSpawnVector = SpawnLocation(vCreate2[num]);
			UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter3::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 28.0f;
		}
		else if (nAnimal2 > 0 && fMana > 32.0f && SelectAction == 4) {
			int num = FMath::RandRange(0, vCreate2.Num() - 1);
			FVector vSpawnVector = SpawnLocation(vCreate2[num]);
			UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter4::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 32.0f;
		}
	}
	else if (Difficult == 3) {
		if (nAnimal1 == 0 && fMana > 60.0f) {
			int num;
			for (int n = 0; n < vSpawn.Num(); n++) {
				num = FMath::RandRange(0, vSpawn.Num() - 1);

				bool Agro = UKismetSystemLibrary::BoxTraceMultiForObjects(GWorld->GetWorld(), vSpawn[num], FVector(0.0f, 0.0f, 0.0f), FVector(200.0f, 200.0f, 300.0f), FRotator(0.0f, 0.0f, 0.0f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);
				if (Agro == false)
					break;
			}
			GWorld->SpawnActor<AAnimalBuilding_Create1>(AAnimalBuilding_Create1::StaticClass(), vSpawn[num], FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 60.0f;
		}
		else if (nAnimal_Resource <= 1 && fMana > 45.0f && SelectAction == 0) {
			int num;
			for (int n = 0; n < vSpawn.Num(); n++) {
				num = FMath::RandRange(0, vSpawn.Num() - 1);

				bool Agro = UKismetSystemLibrary::BoxTraceMultiForObjects(GWorld->GetWorld(), vSpawn[num], FVector(0.0f, 0.0f, 0.0f), FVector(200.0f, 200.0f, 300.0f), FRotator(0.0f, 0.0f, 0.0f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);
				if (Agro == false)
					break;
			}
			GWorld->SpawnActor<AAnimalBuilding_Resource>(AAnimalBuilding_Resource::StaticClass(), vSpawn[num], FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 45.0f;
		}
		else if (nAnimal1 > 0 && fMana > 10.0f && SelectAction == 1) {
			int num = FMath::RandRange(0, vCreate1.Num() - 1);
			FVector vSpawnVector = SpawnLocation(vCreate1[num]);
			UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter1::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 10.0f;
		}
		else if (nAnimal1 > 0 && fMana > 15.0f && SelectAction == 2) {
			int num = FMath::RandRange(0, vCreate1.Num() - 1);
			FVector vSpawnVector = SpawnLocation(vCreate1[num]);
			UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter2::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 15.0f;
		}
		else if (nAnimal2 == 0 && fMana > 85.0f && SelectAction == 5) {
			int num;
			for (int n = 0; n < vSpawn.Num(); n++) {
				num = FMath::RandRange(0, vSpawn.Num() - 1);

				bool Agro = UKismetSystemLibrary::BoxTraceMultiForObjects(GWorld->GetWorld(), vSpawn[num], FVector(0.0f, 0.0f, 0.0f), FVector(200.0f, 200.0f, 300.0f), FRotator(0.0f, 0.0f, 0.0f), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);
				if (Agro == false)
					break;
			}
			GWorld->SpawnActor<AAnimalBuilding_Create2>(AAnimalBuilding_Create2::StaticClass(), vSpawn[num], FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 85.0f;
		}
		else if (nAnimal2 > 0 && fMana > 25.0f && SelectAction == 3) {
			int num = FMath::RandRange(0, vCreate2.Num() - 1);
			FVector vSpawnVector = SpawnLocation(vCreate2[num]);
			UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter3::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 25.0f;
		}
		else if (nAnimal2 > 0 && fMana > 30.0f && SelectAction == 4) {
			int num = FMath::RandRange(0, vCreate2.Num() - 1);
			FVector vSpawnVector = SpawnLocation(vCreate2[num]);
			UAIBlueprintHelperLibrary::SpawnAIFromClass(GWorld->GetWorld(), AAnimalCharacter4::StaticClass(), NULL, vSpawnVector, FRotator(0.0f, 0.0f, 0.0f));
			fMana -= 30.0f;
		}
	}
}

FVector AAnimalAI::SpawnLocation(FVector vLocation)
{

	AFinalProjectGameMode* hGameMode = Cast<AFinalProjectGameMode>(UGameplayStatics::GetGameMode(this));

	int x = 0, y = 0;

	x = vLocation.X * 0.01f;
	y = vLocation.Y * -0.01f;

	vLocation.Z = 150;
	if (hGameMode->mSave[x + 2][y] == '%')
	{
		vLocation.X += 300.0f;
	}

	else if (hGameMode->mSave[x - 2][y] == '%')
	{
		vLocation.X -= 300.0f;
	}

	else if (hGameMode->mSave[x][y + 2] == '%')
	{
		vLocation.Y -= 300.0f;
	}

	else if (hGameMode->mSave[x][y - 2] == '%')
	{
		vLocation.Y += 300.0f;
	}

	else if (hGameMode->mSave[x + 2][y + 2] == '%')
	{
		vLocation.Y -= 300.0f;
		vLocation.X += 300.0f;
	}

	else if (hGameMode->mSave[x - 2][y - 2] == '%')
	{
		vLocation.Y += 300.0f;
		vLocation.X -= 300.0f;
	}

	else if (hGameMode->mSave[x + 2][y + 2] == '%')
	{
		vLocation.Y -= 300.0f;
		vLocation.X += 300.0f;
	}

	else if (hGameMode->mSave[x + 2][y - 2] == '%')
	{
		vLocation.Y += 300.0f;
		vLocation.X += 300.0f;
	}

	else if (hGameMode->mSave[x - 2][y + 2] == '%')
	{
		vLocation.Y -= 300.0f;
		vLocation.X -= 300.0f;
	}

	return vLocation;
}