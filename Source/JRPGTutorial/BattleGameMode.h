// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleGameMode.generated.h"

class AUnitBase;
class ATopDownCamera;
class APartyUnitBase;
class AEnemyUnitBase;

UCLASS()
class JRPGTUTORIAL_API ABattleGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

//Player Controller

	UPROPERTY()
	APlayerController* PlayerController;

//Cameras

	UPROPERTY(EditAnywhere, Category = "Camera Classes")
	TSubclassOf<ATopDownCamera> TopDownCameraClass;

	UPROPERTY()
	ATopDownCamera* TopDownCamera;

//FUNCTIONS

	UFUNCTION()
	void TurnRequest(AUnitBase* Unit);

	UFUNCTION()
	void StartTurn();

	UFUNCTION()
	void ReadyNextTurn();

	UFUNCTION()
	void SetTopDownCamera();

//PROPERTIES

	UPROPERTY()
	TArray<AUnitBase*> OrderArray;

	UPROPERTY()
	bool DoOnce = true;

	//Party Unit Base
	UPROPERTY(EditAnywhere, Category = "Unit Classes")
	TSubclassOf<APartyUnitBase> PartyClass;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> PartyArray;

	//Enemy Unit Base
	UPROPERTY(EditAnywhere, Category = "Unit Classes")
	TSubclassOf<AEnemyUnitBase> EnemyClass;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> EnemyArray;

	
};
