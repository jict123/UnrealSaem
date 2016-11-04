// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "FinalProjectGameMode.h"
#include "FinalProjectPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MainHUD.h"
//#include "MessageLog.h"
//#include "Navigation/PathFollowingComponent.h"

AFinalProjectGameMode::AFinalProjectGameMode()
{
	//기본 플레이어 컨트롤 설정
	PlayerControllerClass = AFinalProjectPlayerController::StaticClass();
	//기본 HUD 클래스 설정
	HUDClass = AMainHUD::StaticClass();
	DefaultPawnClass = NULL;


	fMachinePart = 250;
	fManaStone = 150;
	fSoulStone = 0;

	bHumanTile = false;
	HS1 = false;
	bRe = false;
	Human3 = false;
	HumanCreate3 = false;
}


//bool AFinalProjectGameMode::sSimpleMoveToActor(AController* Controller, const AActor* Goal)
//{
//	UNavigationSystem* NavSys = Controller ? UNavigationSystem::GetCurrent(Controller->GetWorld()) : nullptr;
//	if (NavSys == nullptr || Goal == nullptr || Controller == nullptr || Controller->GetPawn() == nullptr)
//	{
//		/*UE_LOG(LogNavigation, Warning, TEXT("UNavigationSystem::SimpleMoveToActor called for NavSys:%s Controller:%s controlling Pawn:%s with goal actor %s (if any of these is None then there's your problem"),
//			*GetNameSafe(NavSys), *GetNameSafe(Controller), Controller ? *GetNameSafe(Controller->GetPawn()) : TEXT("NULL"), *GetNameSafe(Goal));*/
//		return false;
//	}
//
//	UPathFollowingComponent* PFollowComp = nullptr;
//	Controller->InitNavigationControl(PFollowComp);
//
//	if (PFollowComp == nullptr)
//	{
//		/*FMessageLog("PIE").Warning(FText::Format(
//			LOCTEXT("SimpleMoveErrorNoComp", "SimpleMove failed for {0}: missing components"),
//			FText::FromName(Controller->GetFName())
//			));*/
//		return false;
//	}
//
//	if (!PFollowComp->IsPathFollowingAllowed())
//	{
//		/*FMessageLog("PIE").Warning(FText::Format(
//			LOCTEXT("SimpleMoveErrorMovement", "SimpleMove failed for {0}: movement not allowed"),
//			FText::FromName(Controller->GetFName())
//			));*/
//		return false;
//	}
//
//	if (PFollowComp->HasReached(*Goal))
//	{
//		// make sure previous move request gets aborted
//		PFollowComp->AbortMove(TEXT("Aborting move due to new move request finishing with AlreadyAtGoal"), FAIRequestID::AnyRequest);
//		PFollowComp->SetLastMoveAtGoal(true);
//		return true;
//	}
//	else
//	{
//		const ANavigationData* NavData = NavSys->GetNavDataForProps(Controller->GetNavAgentPropertiesRef());
//		if (NavData)
//		{
//			FPathFindingQuery Query(Controller, *NavData, Controller->GetNavAgentLocation(), Goal->GetActorLocation());
//			FPathFindingResult Result = NavSys->FindPathSync(Query);
//			if (Result.IsSuccessful())
//			{
//				Result.Path->SetGoalActorObservation(*Goal, 100.0f);
//
//				PFollowComp->RequestMove(Result.Path, Goal);
//			}
//			else if (PFollowComp->GetStatus() != EPathFollowingStatus::Idle)
//			{
//				PFollowComp->AbortMove(TEXT("Aborting move due to new move request failing to generate a path"), FAIRequestID::AnyRequest);
//				PFollowComp->SetLastMoveAtGoal(false);
//				return false;
//			}
//		}
//		return true;
//	}
//}