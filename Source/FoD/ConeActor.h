// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ConeActor.generated.h"

UCLASS()
class FOD_API AConeActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AConeActor(const FObjectInitializer& ObjectInitializer);

	UStaticMeshComponent* ConeMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	FVector ConeScale;

	UFUNCTION()
	    void SetConeScale(FVector Size);
	UFUNCTION()
		void OnBeginOverlap(class AActor* Other, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnEndOverlap(class AActor* Other, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);



};

