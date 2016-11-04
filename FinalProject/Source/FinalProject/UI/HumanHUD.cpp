// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "HumanHUD.h"

AHumanHUD::AHumanHUD()
{
	static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("Font'/Game/StarterContent/Shapes/TimeFont'"));
	hFont = HUDFontOb.Object;
}


void AHumanHUD::DrawHUD()
{

}