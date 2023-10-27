// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicCameraInterface.h"
#include "DynamicCamera.generated.h"

class URotatingMovementComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class JRPGTUTORIAL_API ADynamicCamera : public AActor, public IDynamicCameraInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADynamicCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URotatingMovementComponent* RotatingMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY()
	FVector TargetLocation;

//INTERFACE

	virtual void SetLocation(AActor* Actor, FVector Location) override;
	virtual void SetOrbit(bool IsOrbiting) override;

};
