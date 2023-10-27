// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicCamera.h"

#include "GameFramework/RotatingMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADynamicCamera::ADynamicCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm);

	SpringArm->SetWorldRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->TargetArmLength = 500.f;

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovement->bRotationInLocalSpace = false;

}

// Called when the game starts or when spawned
void ADynamicCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADynamicCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GetParentActor())
	{		
		SetActorLocation(FMath::VInterpTo(GetActorLocation(),TargetLocation,UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),5.f));
	}

}

void ADynamicCamera::SetLocation(AActor *Actor, FVector Location)
{
	if(Actor)
	{
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget,EAttachmentRule::KeepWorld,EAttachmentRule::KeepWorld,true);
		AttachToActor(Actor,AttachmentRules);
		Camera->SetRelativeRotation(FRotator(0.f,0.f,0.f));
	}
	else
	{
		TargetLocation = Location;
	}
}

void ADynamicCamera::SetOrbit(bool IsOrbiting)
{
	if(IsOrbiting)
	{
		RotatingMovement->RotationRate = FRotator(0.f,10.f,0.f);
	}else
	{
		RotatingMovement->RotationRate = FRotator(0.f,0.f,0.f);
	}
	SpringArm->bInheritYaw = IsOrbiting;
	
	if(!SpringArm->bInheritYaw)
	{
		SetActorRotation(FRotator(0.f,0.f,0.f));
		SpringArm->SetWorldRotation(FRotator(-45.f, 0.f, 0.f));
	}
}


