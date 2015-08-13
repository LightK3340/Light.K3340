// Fill out your copyright notice in the Description page of Project Settings.

#include "FoD.h"
#include "FPGameMode.h"
#include "FPCharacter.h"
#include "FPHUD.h"

AFPGameMode::AFPGameMode(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	HUDClass = AFPHUD::StaticClass();
	DefaultPawnClass = AFPCharacter::StaticClass();
}

void AFPGameMode::StartPlay(){
	Super::StartPlay();
	StartMatch();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("FPGameMode loaded"));
	}
}



