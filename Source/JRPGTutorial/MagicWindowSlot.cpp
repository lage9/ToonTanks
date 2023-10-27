// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicWindowSlot.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "MagicBase.h"

void UMagicWindowSlot::NativeConstruct()
{
    if (IsValid(MagicBaseClass))
    {
        AMagicBase* DefaultMagicBase = Cast<AMagicBase>(MagicBaseClass->GetDefaultObject());
        
        if (DefaultMagicBase)
        {
            FText MagicName = DefaultMagicBase->MagicName;
            int32 Rank = DefaultMagicBase->Rank;
            FText FormatText = FText::Format(NSLOCTEXT("MagicName", "MagicNameFormat", "{0} (Rank {1})"), MagicName, FText::AsNumber(Rank));
            MagicNameText->SetText(FormatText);
        }

        if(MagicSelectionButton)
        {
            MagicSelectionButton->OnClicked.AddDynamic(this, &UMagicWindowSlot::OnMagicSelectionButton);
        }
    }
}

void UMagicWindowSlot::OnMagicSelectionButton()
{
    AbilityChosenDelegate.Broadcast(MagicBaseClass);
}
