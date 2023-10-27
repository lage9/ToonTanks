// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicWindow.h"

//Widgets
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "MagicWindowSlot.h"
#include "Components/WidgetSwitcher.h"

//Character
#include "UnitBase.h"
#include "CombatComponent.h"

//Magic
#include "DarkMagicaBase.h"
#include "SupportMagicBase.h"



void UMagicWindow::NativeConstruct()
{
    if(DarkMagicCommand)
    {
        DarkMagicCommand->OnClicked.AddDynamic(this, &UMagicWindow::OnDarkMagicCommand);
        UE_LOG(LogTemp, Warning, TEXT("Dark Magic Button Clicked"));
    }

    if(SupportMagicCommand)
    {
        SupportMagicCommand->OnClicked.AddDynamic(this, &UMagicWindow::OnSupportMagicCommand);
        UE_LOG(LogTemp, Warning, TEXT("Support Magic Button Clicked"));
    }
}

void UMagicWindow::OnDarkMagicCommand()
{
    MagicList->ClearChildren();
    if(IsValid(PartyUnit))
    {
       UCombatComponent* CombatComponent = PartyUnit->CombatComponent;
       for(TSubclassOf<ADarkMagicaBase> DarkMagicRef : CombatComponent->DarkMagicAbilities)
       {
            if(DarkMagicRef)
            {
                UMagicWindowSlot* MagicWindowSlot = CreateWidget<UMagicWindowSlot>(GetWorld(), MagicWindowSlotClass);
                if(MagicWindowSlot)
                {
                    MagicWindowSlot->MagicBaseClass = DarkMagicRef;
                    MagicList->AddChild(MagicWindowSlot);   
                    MagicWindowSlot->AbilityChosenDelegate.AddDynamic(this, &UMagicWindow::AbilityChosen);
                }else
                {
                    UE_LOG(LogTemp, Warning, TEXT("NO MAGIC WINDOW SLOT"));
                }
            }
            else
            {
                
            }
       }
       MagicMenuSwitcher->SetActiveWidgetIndex(1);
    }
}

void UMagicWindow::OnSupportMagicCommand()
{
    MagicList->ClearChildren();
    if(IsValid(PartyUnit))
    {
       UCombatComponent* CombatComponent = PartyUnit->CombatComponent;
       for(TSubclassOf<ASupportMagicBase> SupportMagicRef : CombatComponent->SupportMagicAbilities)
       {
            UMagicWindowSlot* MagicWindowSlot = CreateWidget<UMagicWindowSlot>(GetWorld(), MagicWindowSlotClass);
            MagicWindowSlot->MagicBaseClass = SupportMagicRef;
            MagicWindowSlot->AbilityChosenDelegate.AddDynamic(this, &UMagicWindow::AbilityChosen);
            MagicList->AddChild(MagicWindowSlot);
       }
        MagicMenuSwitcher->SetActiveWidgetIndex(1);
    }
}

void UMagicWindow::AbilityChosen(TSubclassOf<AMagicBase> ChosenMagic)
{
    AbilityChosenTargetDelegate.Broadcast(ChosenMagic);
}
