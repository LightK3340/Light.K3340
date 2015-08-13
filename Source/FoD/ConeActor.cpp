// Fill out your copyright notice in the Description page of Project Settings.

#include "FoD.h"
#include "ConeActor.h"


// Sets default values
AConeActor::AConeActor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	ConeMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("ConeMesh"));
	static ConstructorHelpers::FObjectFinder <UMaterialInterface>Material_Transparent(TEXT("Material'/Game/Transparent.Transparent'"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Engine/BasicShapes/Cone.Cone"));
	ConeMesh->SetStaticMesh(MeshObj.Object);
	ConeMesh->SetMaterial(0, Material_Transparent.Object);
	ConeMesh->SetCollisionProfileName(TEXT("Trigger"));
	RootComponent = ConeMesh;
}

// Called when the game starts or when spawned
void AConeActor::BeginPlay()
{
	Super::BeginPlay();
	ConeMesh->OnComponentBeginOverlap.AddDynamic(this, &AConeActor::OnBeginOverlap);
	ConeMesh->OnComponentEndOverlap.AddDynamic(this, &AConeActor::OnEndOverlap);
}

// Called every frame
void AConeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AConeActor::SetConeScale(FVector Size)
{
	ConeMesh->SetWorldScale3D(Size);
}

void AConeActor::OnBeginOverlap(class AActor* Other, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Character enter"));
}

void AConeActor::OnEndOverlap(class AActor* Other, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Character exit"));
}

