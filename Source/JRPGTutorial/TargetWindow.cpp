// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetWindow.h"

//UNIT CHARACTER
#include "UnitBase.h"

//WIDGET
#include "Components/ScrollBox.h"
#include "Blueprint/UserWidget.h"
#include "TargetWindowSlot.h"

//BUTTON
#include "Components/Button.h"

//GAMEPLAY
#include "Kismet/GameplayStatics.h"
#include "BattleGameMode.h"

//Unit Character
#include "PartyUnitBase.h"
#include "EnemyUnitBase.h"

void UTargetWindow::NativeConstruct()
{
}

void UTargetWindow::OnTargetSelected(AEnemyUnitBase * SelectedEnemyUnit)
{
    OnTargetSelectionButton(SelectedEnemyUnit);
}

void UTargetWindow::OnTargetSelectionButton(AEnemyUnitBase* SelectedEnemyUnit)
{
    if (PartyUnit && SelectedEnemyUnit)
    {
        if(MagicBaseRef)
        {
            PartyUnit->CombatComponent->MagicCommand_Implementation(Cast<AUnitBase>(SelectedEnemyUnit), MagicBaseRef);
        }
        else
        {
            PartyUnit->CombatComponent->AttackCommand_Implementation(Cast<AUnitBase>(SelectedEnemyUnit));
        }
    }
}

void UTargetWindow::PopulateTargetList()
{
    TargetList->ClearChildren();
    BattleGameMode = Cast<ABattleGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

    for (AActor* EnemyUnit : BattleGameMode->EnemyArray)
    {
        if (TargetWindowSlotClass)
        {
            if (EnemyUnit)
            {
                // Create a new instance of TargetWindowSlot for each EnemyUnit
                UTargetWindowSlot* TargetWindowSlot = CreateWidget<UTargetWindowSlot>(GetWorld(), TargetWindowSlotClass);
                TargetWindowSlot->Unit = Cast<AEnemyUnitBase>(EnemyUnit);
                UE_LOG(LogTemp, Warning, TEXT("UNIT FROM TARGET SLOT : %s"), *TargetWindowSlot->Unit->GetName());
                TargetWindowSlot->TargetSelectionDelegate.AddDynamic(this, &UTargetWindow::OnTargetSelected);
                TargetList->AddChild(TargetWindowSlot);
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Target Window Slot Class Not specified"));
        }
    }
}

