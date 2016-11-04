// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "MainHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FinalProjectGameMode.h"
#include "HumanHUD.h"

AMainHUD::AMainHUD()
{
	static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("Font'/Game/StarterContent/Shapes/TimeFont'"));
	HUDFont = HUDFontOb.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D>ManaTexture(TEXT("Texture'/Game/FinalProject/Texture/manastone'"));
	ManaStone = ManaTexture.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D>PartTexture(TEXT("Texture'/Game/FinalProject/Texture/MachinePart'"));
	MachinePart = PartTexture.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D>SoulTexture(TEXT("Texture'/Game/FinalProject/Texture/soulstone'"));
	SoulStone = SoulTexture.Object;

}

void AMainHUD::DrawHUD()
{
		FVector2D ScreenSize = FVector2D(Canvas->SizeX, Canvas->SizeY);

		Super::DrawHUD();

		AFinalProjectGameMode* uGameMode;
		uGameMode = Cast<AFinalProjectGameMode>(UGameplayStatics::GetGameMode(this));
		if (uGameMode->bHumanTile == true) {

		nManaStone = uGameMode->fManaStone;
		nMachinePart = uGameMode->fMachinePart;
		nSoulStone = uGameMode->fSoulStone;
		UWorld* const World = GetWorld();
		int fTime = World->GetTimeSeconds();

		if (fTime % 10 == 0)
		{
			if (uGameMode->bRe == true)
				uGameMode->bRe = false;
			else
				uGameMode->bRe = true;
		}
		//시간
		FString sTime = FString::Printf(TEXT("%d"), fTime);
		DrawText(sTime, FColor::White, ScreenSize.X / 2, 25, HUDFont, 2.0f);

		//기계부품
		DrawTextureSimple(MachinePart, 0, 10, 0.7f);
		FString sMachinePart = FString::Printf(TEXT("%d"), nMachinePart);
		DrawText(sMachinePart, FColor::White, 80, 25, HUDFont, 1.5f);

		//마나스톤
		DrawTextureSimple(ManaStone, 150, 10, 0.7f);
		FString sManaStone = FString::Printf(TEXT("%d"), nManaStone);
		DrawText(sManaStone, FColor::White, 230, 25, HUDFont, 1.5f);

		//소울스톤
		DrawTextureSimple(SoulStone, 300, 10, 0.7f);
		FString sSoulStone = FString::Printf(TEXT("%d"), nSoulStone);
		DrawText(sSoulStone, FColor::White, 380, 25, HUDFont, 1.5f);
	}
	/*FCanvas* Canvass;
	FHUDHitBox* hudHitBox;
	hudHitBox->Draw(Canvass, FColor::White);
	FName hName=hudHitBox->GetName;
	NotifyHitBoxClick(hName);
	*/

	/*AHumanHUD* hHUD;
	hHUD = Cast<AHumanHUD>();*/
	/*if (uGameMode->bHumanTile == true)
	{
		//DrawHUD();
	}*/
}

