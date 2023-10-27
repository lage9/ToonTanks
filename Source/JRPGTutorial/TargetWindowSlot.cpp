// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetWindowSlot.h"

void UTargetWindowSlot::NativeConstruct()
{
    if (TargetSelectionButtom)
    {
        TargetSelectionButtom->OnClicked.AddDynamic(this, &UTargetWindowSlot::HandleTargetSelection);
    }
}

void UTargetWindowSlot::HandleTargetSelection()
{
    if (Unit && TargetSelectionDelegate.IsBound())
    {
        // Cast AUnitBase to AEnemyUnitBase (if possible)
        AEnemyUnitBase* SelectedEnemyUnit = Cast<AEnemyUnitBase>(Unit);
        
        if (SelectedEnemyUnit)
        {
            // Call the custom event dispatcher with the selected enemy unit
            TargetSelectionDelegate.Broadcast(SelectedEnemyUnit);
        }
    }
}
