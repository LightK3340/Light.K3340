// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "FPHUD.generated.h"

/**
*
*/
UCLASS()
class FOD_API AFPHUD : public AHUD
{
	GENERATED_BODY()
public:
	AFPHUD(const FObjectInitializer& ObjectInitializer);
	virtual void DrawHUD() override;
private:
	UTexture2D* CrosshairTex;



};
