// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkMagicaBase.h"

#include "Kismet/GameplayStatics.h"

//character
#include "UnitBase.h"
#include "CombatComponent.h"

void ADarkMagicaBase::DestroyProjectile()
{
}

void ADarkMagicaBase::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
    AUnitBase* DamageCauser = Cast<AUnitBase>(GetInstigator());
    UCombatComponent* ComnbatComponentDmgCauser = DamageCauser->CombatComponent;
    AActor* DamagedActor = Cast<AActor>(SpellTarget);
    UGameplayStatics::ApplyDamage(DamagedActor,ComnbatComponentDmgCauser->CalculateMagicDamage(this->GetClass()),nullptr,DamageCauser,DamageTypeClass);
}
