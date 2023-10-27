// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitBattleHUD.h"

//WIDGETS
#include "ActionCommands.h"
#include "TargetWindow.h"
#include "Components/Button.h"
#include "MagicWindow.h"
#include "CombatComponent.h"

void UUnitBattleHUD::NativeConstruct()
{   
    if(Unit && MagicWindow)
    {
        MagicWindow->PartyUnit = Unit;
    }
    if (ActionCommands->AttackCommand)
    {
        ActionCommands->AttackCommand->OnClicked.AddDynamic(this, &UUnitBattleHUD::OnAttackCommand);
    }

    if (ActionCommands->MagicCommand)
    {
        ActionCommands->MagicCommand->OnClicked.AddDynamic(this, &UUnitBattleHUD::OnMagicCommand);
    }

    if (ActionCommands->TechniquesCommand)
    {
        ActionCommands->TechniquesCommand->OnClicked.AddDynamic(this, &UUnitBattleHUD::OnTechniquesCommand);
    }

    if (ActionCommands->ItemsCommand)
    {
        ActionCommands->ItemsCommand->OnClicked.AddDynamic(this, &UUnitBattleHUD::OnItemsCommand);
    }

    if(TargetWindow->BackCommand)
    {
        TargetWindow->BackCommand->OnClicked.AddDynamic(this, &UUnitBattleHUD::BackTargetCommand);
    }

    if(MagicWindow->BackCommand)
    {
        MagicWindow->BackCommand->OnClicked.AddDynamic(this, &UUnitBattleHUD::BackMagicCommand);
    }
}

void UUnitBattleHUD::OnAttackCommand()
{
    TargetWindow->PopulateTargetList();
    ShowTargetAnimation();
}

void UUnitBattleHUD::OnMagicCommand()
{
    if(Unit->CombatComponent->DarkMagicAbilities.Num() > 0 || Unit->CombatComponent->SupportMagicAbilities.Num() > 0)
    {
        MagicWindow->AbilityChosenTargetDelegate.AddDynamic(this, &UUnitBattleHUD::AbilityChosen);
        ShowMagicAnimation();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No Dark/Support Magic Abilities for this Unit"));
    }
}

void UUnitBattleHUD::OnTechniquesCommand()
{
}

void UUnitBattleHUD::OnItemsCommand()
{
}

void UUnitBattleHUD::BackTargetCommand()
{
    BackTargetAnimation();
}

void UUnitBattleHUD::BackMagicCommand()
{
    BackMagicAnimation();
}

void UUnitBattleHUD::AbilityChosen(TSubclassOf<AMagicBase> ChosenMagic)

{
    OnAttackCommand();
    TargetWindow->MagicBaseRef = ChosenMagic;
}
