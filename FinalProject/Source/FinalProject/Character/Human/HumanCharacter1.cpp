// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "HumanCharacter1.h"
#include "Character/Human/HumanAIController.h"
#include "FinalProjectGameMode.h"
#include "BehaviorTree/HumanBehaviorTree.h"

// Sets default values
AHumanCharacter1::AHumanCharacter1()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	hHp = 100.0f;		//초기 hp값
	
	// Set StaticMesh Object
	static ConstructorHelpers::FObjectFinder <USkeletalMesh>SkelaetalMesh(TEXT("Skeleton'/Game/MixamoAnimPack/Mixamo_Adam/Mesh/Maximo_Adam.Maximo_Adam'"));
	// Set Material Texture
	static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_(TEXT("Material'/Game/MixamoAnimPack/Mixamo_Adam/Materials/M_Maximo_Adam_Body.M_Maximo_Adam_Body'"));
	//애니메이션 스테이트머신
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> lAnimBlueprint(TEXT("AnimBlueprint'/Game/MixamoAnimPack/Mixamo_Adam/Anims/MixamoAnimBP_Adam.MixamoAnimBP_Adam'"));
	static UClass* lAnimBlueprintClass = (UClass*)lAnimBlueprint.Object->GeneratedClass;

	//Component Setting
	if (SkelaetalMesh.Object) {
		Mesh->AttachTo(RootComponent);
		Mesh->SetSkeletalMesh(SkelaetalMesh.Object);
		Mesh->SetMaterial(0, Material_.Object);
		Mesh->SetRelativeRotation(FQuat(0.0f, 0.0f, -90.0f, 90.0f));
		Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		Mesh->SetAnimInstanceClass(lAnimBlueprintClass);

	}

	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -75.0f));
	Mesh->SetWorldScale3D(FVector(2.00f, 2.00f, 2.00f));
	CapsuleComponent->SetWorldScale3D(FVector(0.25f, 0.25f, 0.25f));
	this->CharacterMovement->MaxWalkSpeed = 250.0f;
	this->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;	//스폰위치에 액터가 있을경우 그 옆으로 스폰

	this->AIControllerClass = AHumanAIController::StaticClass();				//ai 컨트롤러 부착
}

void AHumanCharacter1::BeginPlay()
{
	Super::BeginPlay();
}

void AHumanCharacter1::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called every frame
void AHumanCharacter1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDeath == true) {
		death_time = death_time + DeltaTime;
		if (death_time > 0.2f)
			this->Destroy();
	}
	else {
		if (bFirst == true) {
			for (int i = 0; i < hGameMode->Target.Num(); i++) {
				if ((this->GetActorLocation().X <= hGameMode->Target[i]->GetActorLocation().X + 50.0f && this->GetActorLocation().X >= hGameMode->Target[i]->GetActorLocation().X - 50.0f) && (this->GetActorLocation().Y <= hGameMode->Target[i]->GetActorLocation().Y + 50.0f && this->GetActorLocation().Y >= hGameMode->Target[i]->GetActorLocation().Y - 50.0f)) {
					nNum = i;
					bFirst = false;
				}
			}
		}
		if (bAgro == true) {
			Attack_time += DeltaTime;
			if (Attack_time >= 1.5f) {
				bDamage = true;
				Attack_time = 0.0f;
			}
		}
		else
			Attack_time = 0.0f;

		if (((this->GetActorLocation().X <= hGameMode->Target[nNum]->GetActorLocation().X + 75.0f) && (this->GetActorLocation().X >= hGameMode->Target[nNum]->GetActorLocation().X - 75.0f)) && ((this->GetActorLocation().Y <= hGameMode->Target[nNum]->GetActorLocation().Y + 75.0f) && (this->GetActorLocation().Y >= hGameMode->Target[nNum]->GetActorLocation().Y - 75.0f))) {
			nNum--;
		}


		if (nNum == -1)
			nNum = hGameMode->Target.Num() - 1;

		if (nNum == hGameMode->Target.Num())
			nNum = 0;

		root = new Sequence;
		sequence1 = new Sequence;
		sequence2 = new Sequence;
		selector = new Selector;
		checkhp = new hCheckHp(this->Controller);
		checkagro = new hCheckAgro(this->Controller);
		move = new hMoveTask(this->Controller, hGameMode->Target[nNum]);
		movetarget = new hMoveTargetTask(this->Controller, AgroTarget, 300.0F);
		attack = new hAttackTask(this->Controller, AgroTarget,bDamage,12.0f);

		root->addChild(sequence1);
		sequence1->addChild(checkhp);
		sequence1->addChild(selector);
		selector->addChild(sequence2);
		sequence2->addChild(checkagro);
		sequence2->addChild(movetarget);
		sequence2->addChild(attack);
		selector->addChild(move);

		root->run();
	}
}

// Called to bind functionality to input
void AHumanCharacter1::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}



