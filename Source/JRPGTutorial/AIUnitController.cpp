#include "AIUnitController.h"
#include "CombatComponent.h"

//Unit Character
#include "UnitBase.h"

//Game Mode
#include "BattleGameMode.h"
#include "Kismet/GameplayStatics.h"

void AAIUnitController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult &Result)
{
    AUnitBase* UnitBase = Cast<AUnitBase>(GetPawn());

    if(UnitBase && DoOnce)
    {
    if(UnitBase->CombatComponent->IsRanged)
    {
        if(UnitBase->CombatComponent->IsMagic)
        {
            
            if(UnitBase->CombatComponent->IsDarkMagic)
            {
                UE_LOG(LogTemp, Error, TEXT("Dark Magic Spawned"));
                AttackAnimationTime = UnitBase->PlayDarkMagicMontage();
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Support Magic Spawned"));
                AttackAnimationTime = UnitBase->PlaySupportMagicMontage();
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("RANGED PLAYER"));
            AttackAnimationTime = UnitBase->PlayRangedAttackMontage();
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("MELEE PLAYER"));
        AttackAnimationTime = UnitBase->PlayMelleeAttackMontage();
    }


    if(AttackAnimationTime > 0)
    {
        GetWorldTimerManager().SetTimer(AttackAnimationTimer, UnitBase, &AUnitBase::GoBackToOriginalLocation,AttackAnimationTime,false);
    }

    ABattleGameMode* BattleGameMode = Cast<ABattleGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if(BattleGameMode)
    {
        GetWorldTimerManager().SetTimer(BackToPositonTimer, UnitBase, &AUnitBase::AdjustRotation, BackToPositon += AttackAnimationTime, false);
        GetWorldTimerManager().SetTimer(FinishingTurn, UnitBase->CombatComponent, &UCombatComponent::EndUnitTurn,BackToPositon,false);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("NO GAME MODE IN AI CONTROLLER CLASS"));
    }
    DoOnce = false;

    }
}
