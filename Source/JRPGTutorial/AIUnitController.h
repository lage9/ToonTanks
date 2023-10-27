// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIUnitController.generated.h"

UCLASS()
class JRPGTUTORIAL_API AAIUnitController : public AAIController
{
	GENERATED_BODY()

public:

//Timer handler

	UPROPERTY()
	FTimerHandle AttackAnimationTimer;

	UPROPERTY()
	float AttackAnimationTime;

	UPROPERTY()
	FTimerHandle FinishingTurn;

	UPROPERTY()
	float NextTurnDelay;

	UPROPERTY()
	FTimerHandle BackToPositonTimer;

	UPROPERTY()
	float BackToPositon = 1.5f; // THE SUM OF THE MONTAGES PLAYING + THE TIME TO GO BACK TO HIS LOCATION

// Attack Movement

	UPROPERTY()
	bool DoOnce = true;

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
