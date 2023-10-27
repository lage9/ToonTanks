// Fill out your copyright notice in the Description page of Project Settings.


#include "DealDamageNotify.h"

//Character
#include "UnitBase.h"
#include "CombatComponent.h"

//Gameplay
#include "Kismet/GameplayStatics.h"

void UDealDamageNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{
    UE_LOG(LogTemp, Error, TEXT("UDealDamageNotify."));
    AUnitBase* DamageCauser = Cast<AUnitBase>(MeshComp->GetOwner());
    if(DamageCauser)
    {
        UCombatComponent* CombatComponent = DamageCauser->CombatComponent;

        if(CombatComponent)
        {
            AActor* Target = Cast<AUnitBase>(CombatComponent->TargetChoosed);

        if(Target)
        {
            UGameplayStatics::ApplyDamage(Target,CombatComponent->CalculateDamage(),nullptr,DamageCauser, DamageTypeClass);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("No target in UDealDamageNotify."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("UDealDamageNotify."));
    }
    }
}
