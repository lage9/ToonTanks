// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGameMode.h"

//Unit Character
#include "UnitBase.h"
#include "CombatComponent.h"
#include "PartyUnitBase.h"
#include "EnemyUnitBase.h"

//Cameras
#include "TopDownCamera.h"
#include "Kismet/GameplayStatics.h"

void ABattleGameMode::BeginPlay()
{
    TopDownCamera = Cast<ATopDownCamera>(UGameplayStatics::GetActorOfClass(GetWorld(), TopDownCameraClass));
    PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
    SetTopDownCamera();
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), PartyClass, PartyArray);
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyClass, EnemyArray);

    for (AActor* PartyActor : PartyArray)
    {
        UE_LOG(LogTemp, Warning, TEXT("PartyArray Element Class: %s"), *PartyActor->GetClass()->GetName());
    }

    for (AActor* EnemyActor : EnemyArray)
    {
        UE_LOG(LogTemp, Warning, TEXT("EnemyArray Element Class: %s"), *EnemyActor->GetClass()->GetName());
    }
}

void ABattleGameMode::TurnRequest(AUnitBase *Unit)
{
    OrderArray.AddUnique(Unit);
    StartTurn();
}

void ABattleGameMode::StartTurn()
{
    if(DoOnce)
    {
        DoOnce = false;
        if(OrderArray[0])
        {
            OrderArray[0]->CombatComponent->StartUnitTurn();
            OrderArray.RemoveAt(0);
        }
    }
}

void ABattleGameMode::ReadyNextTurn()
{
    if(IsValid(OrderArray[0]))
    {
        DoOnce = true;
        StartTurn();   
    }
}

void ABattleGameMode::SetTopDownCamera()
{
    PlayerController->SetViewTargetWithBlend(TopDownCamera,0.f,VTBlend_Linear,0.f,false);
}
