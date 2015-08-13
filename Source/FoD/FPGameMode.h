// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "FPGameMode.generated.h"

/**
*
*/
UCLASS()
class FOD_API AFPGameMode : public AGameMode
{
	GENERATED_BODY()

	AFPGameMode(const FObjectInitializer& ObjectInitializer);
	virtual void StartPlay() override;




};
