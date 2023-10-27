// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyWidgetSlot.h"

#include "UnitBase.h"
#include "CombatComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Internationalization/Text.h"

void UPartyWidgetSlot::NativeConstruct()
{
    Super::NativeConstruct();
    if(Unit)
    {
        SetBeginBattleStats();
        Unit->OnUnitTakeDamage.AddDynamic(this, &UPartyWidgetSlot::HandleDamage);   
    }
}

void UPartyWidgetSlot::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    SetCharacterActionBar();
}

void UPartyWidgetSlot::SetCharacterActionBar()
{
    if(Unit)
    {
        LerpSpeed = 0.01 * Unit->CombatComponent->HasteTime;

        PercentBar = FMath::Lerp(CharacterActionBar->GetPercent(), 1.f, LerpSpeed);
        CharacterActionBar->SetPercent(PercentBar);
    }else
    {
        UE_LOG(LogTemp, Warning, TEXT("Unit in PartyWidgetSlot not null"));
    }
}

void UPartyWidgetSlot::HandleDamage(float DamageTaken, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
    UE_LOG(LogTemp, Error, TEXT("HANDLE DAMAGE"));
    Unit->CurrentHP -= DamageTaken;
    SetBeginBattleStats();
}

void UPartyWidgetSlot::SetBeginBattleStats()
{
    
    FNumberFormattingOptions NoDecimalPlaces;
    NoDecimalPlaces.MaximumFractionalDigits = 0;

    if(DoOnce)
    {
        DoOnce = false;
        UnitNameText->SetText(Unit->Name);
        HPMaxText->SetText(FText::AsNumber(Unit->MaxHP, &NoDecimalPlaces));
        MPMaxText->SetText(FText::AsNumber(Unit->MaxMP, &NoDecimalPlaces));
    }
    
    HPCurrentText->SetText(FText::AsNumber(Unit->CurrentHP, &NoDecimalPlaces));
    MPCurrentText->SetText(FText::AsNumber(Unit->CurrentMP, &NoDecimalPlaces));
}
