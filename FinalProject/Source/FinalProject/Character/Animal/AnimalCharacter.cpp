// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "AnimalCharacter.h"
#include "FinalProjectGameMode.h"
#include "BehaviorTree/AnimalBehaviorTree.h"
#include "Character/Animal/AnimalAIController.h"
#include "Character/Human/HumanCharacter.h"

// Sets default values
AAnimalCharacter::AAnimalCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	////static ConstructorHelpers::FObjectFinder <USkeletalMesh>SkelaetalMesh(TEXT("Skeleton'/Game/InfinityBladeAdversaries/Enemy/Enemy_Chicken/S_Survival_CA_Chicken.S_Survival_CA_Chicken'"));
	////static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_(TEXT("Material'/Game/InfinityBladeAdversaries/Enemy/Enemy_Chicken/Materials/M_EnemyChicken.M_EnemyChicken'"));
	//aHp = 200.0f;
	//nNum = 0;
	//// Set StaticMesh Object
	//static ConstructorHelpers::FObjectFinder <USkeletalMesh>SkelaetalMesh(TEXT("Skeleton'/Game/InfinityBladeAdversaries/Enemy/Enemy_Gruntling_Glacer/SK_Gruntling_Glacer.SK_Gruntling_Glacer'"));
	//// Set Material Texture
	//static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_(TEXT("Material'/Game/InfinityBladeAdversaries/Enemy/Enemy_Gruntling_Glacer/Materials/CharM_Gruntling_Glacer.CharM_Gruntling_Glacer'"));
	////애니메이션 스테이트머신
	//static ConstructorHelpers::FObjectFinder<UAnimBlueprint> lAnimBlueprint(TEXT("AnimBlueprint'/Game/InfinityBladeAdversaries/Enemy/Enemy_Gruntling_Glacer/GlacerAnim.GlacerAnim'"));
	//static UClass* lAnimBlueprintClass = (UClass*)lAnimBlueprint.Object->GeneratedClass;

	////Component Setting
	//if (SkelaetalMesh.Object) {
	//	Mesh->AttachTo(RootComponent);
	//	Mesh->SetSkeletalMesh(SkelaetalMesh.Object);
	//	Mesh->SetMaterial(0, Material_.Object);
	//	Mesh->SetRelativeRotation(FQuat(0.0f, 0.0f, -90.0f, 90.0f));
	//	//Mesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	//	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	//	Mesh->SetAnimInstanceClass(lAnimBlueprintClass);
	//}
	//Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -75.0f));

	//this->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	//this->AIControllerClass = AAnimalAIController::StaticClass();				//ai 컨트롤러 부착
	//this->CharacterMovement->MaxWalkSpeed = 200.0f;

}

// Called when the game starts or when spawned
void AAnimalCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAnimalCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//AFinalProjectGameMode* aGameMode = Cast<AFinalProjectGameMode>(UGameplayStatics::GetGameMode(this));

	//if (bDeath == true) {
	//	death_time = death_time + DeltaTime;
	//	UE_LOG(LogClass, Log, TEXT("%f"), death_time);
	//	if (death_time > 1.39f)
	//		this->Destroy();
	//}
	//else {

	//	if (bFirst == true) {
	//		for (int i = 0; i < aGameMode->Target.Num(); i++) {
	//			if ((this->GetActorLocation().X <= aGameMode->Target[i]->GetActorLocation().X + 50.0f && this->GetActorLocation().X >= aGameMode->Target[i]->GetActorLocation().X - 50.0f) && (this->GetActorLocation().Y <= aGameMode->Target[i]->GetActorLocation().Y + 50.0f && this->GetActorLocation().Y >= aGameMode->Target[i]->GetActorLocation().Y - 50.0f)) {
	//				nNum = i;
	//				bRe = aGameMode->bRe;
	//				bFirst = false;
	//			}
	//		}
	//	}
	//	if (bAgro == true) {
	//		Attack_time += DeltaTime;
	//		if (Attack_time >= 2.033f) {
	//			bDamage = true;
	//			Attack_time = 0.0f;
	//		}
	//	}
	//	else
	//		Attack_time = 0.0f;

	//	/*if (((this->GetActorLocation().X <= aGameMode->Target[nNum]->GetActorLocation().X + 50.0f) && (this->GetActorLocation().X >= aGameMode->Target[nNum]->GetActorLocation().X - 50.0f)) && ((this->GetActorLocation().Y <= aGameMode->Target[nNum]->GetActorLocation().Y + 50.0f) && (this->GetActorLocation().Y >= aGameMode->Target[nNum]->GetActorLocation().Y - 50.0f))) {
	//		nNum++;
	//	}*/


	//	if (nNum == -1)
	//		nNum = aGameMode->Target.Num() - 1;

	//	if (nNum == aGameMode->Target.Num())
	//		nNum = 0;

	//	//behavior tree
	//	Sequence *root = new Sequence;
	//	Sequence *sequence1 = new Sequence;
	//	Sequence *sequence2 = new Sequence;
	//	Selector* selector = new Selector;
	//	aCheckHp* checkhp = new aCheckHp(this->Controller);
	//	aCheckAgro* checkagro = new aCheckAgro(this->Controller);
	//	aMoveTask* move = new aMoveTask(this->Controller, aGameMode->Target[nNum],bRe);
	//	aMoveTask2* move2 = new aMoveTask2(this->Controller, aGameMode->Target[nNum], bRe);
	//	aMoveTargetTask* target = new aMoveTargetTask(this->Controller, AgroTarget, 300.0F);
	//	aAttackTask* attack = new aAttackTask(this->Controller, AgroTarget,bDamage, 25.0f);

	//	root->addChild(sequence1);
	//	sequence1->addChild(checkhp);
	//	sequence1->addChild(selector);
	//	selector->addChild(sequence2);
	//	sequence2->addChild(checkagro);
	//	sequence2->addChild(target);
	//	sequence2->addChild(attack);
	//	selector->addChild(move);
	//	selector->addChild(move2);

	//	root->run();

	//	//UE_LOG(LogClass, Log, TEXT("%d"), nNum);
	//}
}

// Called to bind functionality to input
void AAnimalCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

