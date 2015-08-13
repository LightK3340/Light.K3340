// Fill out your copyright notice in the Description page of Project Settings.

#include "FoD.h"
#include "ConeActor.h"
#include "FPCharacter.h"


// Sets default values
AFPCharacter::AFPCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("FPCharacter Loaded"));
	}

}

// Called every frame
void AFPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (place_cone_state == true){ //может есть способ не проверять это в каждом кадре?
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::SanitizeFloat(GetInputAxisValue("Turn")));
		cur_light_actor->SetActorRotation(FRotator(cur_light_actor->GetActorRotation().Pitch - 10 * GetInputAxisValue("LookUp"), cur_light_actor->GetActorRotation().Yaw - 10 * GetInputAxisValue("Turn"), 0));
	}
}

// Called to bind functionality to input
void AFPCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	InputComponent->BindAxis("MoveForward", this, &AFPCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFPCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &AFPCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AFPCharacter::AddControllerPitchInput);
	InputComponent->BindAction("PlaceCone", IE_Pressed, this, &AFPCharacter::PlaceCone);
}

void AFPCharacter::MoveForward(float val){
	if ((Controller != NULL) && (val != 0.0f)){
		FRotator rotation = Controller->GetControlRotation();
		const FVector direction = FRotationMatrix(rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(direction, val);
	}
}

void AFPCharacter::MoveRight(float val){
	if ((Controller != NULL) && (val != 0.0f)){
		FRotator rotation = Controller->GetControlRotation();
		const FVector direction = FRotationMatrix(rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(direction, val);
	}
}

void AFPCharacter::PlaceCone(){
	if (place_cone_state == false){
		bool success = false;
		FHitResult ray_hit = GetRaycast();
		if (ray_hit.GetActor() != NULL){
			FRotator cone_rotation = ray_hit.ImpactNormal.Rotation();
			cone_rotation.Pitch += 90;
			FVector cone_position = ray_hit.Location + (ray_hit.ImpactNormal * 1500);
			AConeActor* SpawnedCone = (AConeActor*)GetWorld()->SpawnActor<AConeActor>(AConeActor::StaticClass());
			FVector ConeSize = FVector(16, 16, 30);
			SpawnedCone->SetConeScale(ConeSize);
			SpawnedCone->SetActorLocation(FVector(cone_position));
			SpawnedCone->SetActorRotation(cone_rotation);
			ASpotLight* SpotLight = (ASpotLight*)GetWorld()->SpawnActor<ASpotLight>(ASpotLight::StaticClass(), FVector(ray_hit.Location), ray_hit.ImpactNormal.Rotation());
			SpotLight->SetEnabled(false); //Не ебу почему чтобы заработало сначала нужно вырубить, а потом врубить свет (разобраться)
			SpotLight->SpotLightComponent->AttenuationRadius = 3600.0;
			SpotLight->SpotLightComponent->OuterConeAngle = 16.0;
			SpotLight->SpotLightComponent->InnerConeAngle = 9.0;
			SpotLight->SpotLightComponent->SourceLength = 910.0;
			SpotLight->SetBrightness(100000);
			SpotLight->SetEnabled(true);
			SpotLight->SetActorLocation(ray_hit.Location);
			SpotLight->SetActorRotation(cone_rotation);
			SpawnedCone->AttachRootComponentToActor(SpotLight, NAME_None, EAttachLocation::KeepWorldPosition, false);
			SpotLight->SetMobility(EComponentMobility::Movable);
			place_cone_state = true;
			cur_light_actor = SpotLight;
		}
	}
	else
		place_cone_state = false;
}

FHitResult AFPCharacter::GetRaycast(){
	FVector CamPos;
	FRotator CamRot;
	Controller->GetPlayerViewPoint(CamPos, CamRot);
	FCollisionQueryParams TraceParams(FName(TEXT("WeaponTrace")), true, this);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;

	const FVector StartTrace = CamPos; // trace start is the camera location
	const FVector Direction = CamRot.Vector();
	const FVector EndTrace = StartTrace + Direction * 10000; // and trace end is the camera location + an offset in the direction you are looking, the 200 is the distance at wich it checks

	FHitResult Hit(ForceInit); //что за ForceInit???
	GetWorld()->LineTraceSingle(Hit, StartTrace, EndTrace, ECC_Visibility, TraceParams);
	return Hit;
}




