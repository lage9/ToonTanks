// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitBase.h"
#include "EnemyUnitBase.h"

#include "CombatComponent.h"
#include "AIUnitController.h"

//Ranged Attack
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUnitBase::AUnitBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
}

// Called when the game starts or when spawned
void AUnitBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUnitBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AUnitBase::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	if(HitMontage)
	{
		PlayAnimMontage(HitMontage, 1.f, NAME_None);
		float DamageAfterResistace = CombatComponent->CalculateDamageResistance(DamageAmount);
		float DamagaTaken = FMath::Clamp(DamageAfterResistace,0, MaxHP);

		OnUnitTakeDamage.Broadcast(DamagaTaken, DamageEvent, EventInstigator, DamageCauser);

		return DamageAfterResistace;
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("No damage."));
	}
    return 0.0f;
}

float AUnitBase::PlayMelleeAttackMontage()
{
	if(MeleeAttackMontage.Num() > 0)
	{
		int32 RandomAnimIndex = FMath::RandRange(0, MeleeAttackMontage.Num() - 1);
		UAnimMontage* MeleeMontage = MeleeAttackMontage[RandomAnimIndex];

		if(MeleeMontage)
		{
			return PlayAnimMontage(MeleeMontage,1.f,NAME_None);
		}
	}
	return 0.f;
}

float AUnitBase::PlayRangedAttackMontage()
{
	if(RangedAttackMontage.Num() > 0)
	{
		int32 RandomAnimIndex = FMath::RandRange(0, RangedAttackMontage.Num() - 1);
		UAnimMontage* RangedMontage = RangedAttackMontage[RandomAnimIndex];

		if(RangedMontage)
		{
			AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,GetActorLocation(), GetActorRotation());
			if(SpawnedProjectile)
			{
				SpawnedProjectile->SetInstigator(this);
				return PlayAnimMontage(RangedMontage,1.f,NAME_None);
			}else
			{
				UE_LOG(LogTemp, Error, TEXT("RANGED NOT SPAWNING"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No Ranged Montage animation for this class."));
		}
	}
	return 0.f;
}

float AUnitBase::PlayDarkMagicMontage()
{
	if(DarkMagicAttackMontage.Num() > 0)
	{
		int32 RandomAnimIndex = FMath::RandRange(0, DarkMagicAttackMontage.Num() - 1);
		UAnimMontage* MagicMontage = DarkMagicAttackMontage[RandomAnimIndex];
		if(MagicMontage)
		{
			ADarkMagicaBase* DarkMagic = GetWorld()->SpawnActor<ADarkMagicaBase>(DarkMagicClass,GetActorLocation(), GetActorRotation());
			if(DarkMagic)
			{
				DarkMagic->SetInstigator(this);
				DarkMagic->SpellTarget = this;
				return PlayAnimMontage(MagicMontage,1.f,NAME_None);
			}
			else
			{
			UE_LOG(LogTemp, Error, TEXT("Magic NOT SPAWNING"));
			}
		}
	}
	return 0.f;
}

float AUnitBase::PlaySupportMagicMontage()
{
	if(SupportMagicAttackMontage.Num() > 0)
	{
		int32 RandomAnimIndex = FMath::RandRange(0, SupportMagicAttackMontage.Num() - 1);
		UAnimMontage* MagicMontage = SupportMagicAttackMontage[RandomAnimIndex];

		if(MagicMontage)
		{
			ASupportMagicBase* SupportMagic = GetWorld()->SpawnActor<ASupportMagicBase>(SupportMagicClass,GetActorLocation(), GetActorRotation());
			if(SupportMagic)
			{
				UE_LOG(LogTemp, Error, TEXT("Magic Support spawned"));
				SupportMagic->SetInstigator(this);
				SupportMagic->SpellTarget = this;
				return PlayAnimMontage(MagicMontage,1.f,NAME_None);
			}
			else
			{
			UE_LOG(LogTemp, Error, TEXT("Magic NOT SPAWNING"));
			}
		}
	}
	return 0.0f;
}

void AUnitBase::AdjustRotation()
{
	FRotator TargetRotation = FRotator(CombatComponent->BattlePositionTransform.GetRotation());
	FRotator CurrentRotation = GetActorRotation();

	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 500.f);

	SetActorRotation(NewRotation, ETeleportType::None);
}

void AUnitBase::SetMaxStats(float HP, float MP,int32 IntHP, int32 IntMP)
{
	MaxHP = HP * IntHP;
	MaxMP = MP * IntMP;

	CurrentHP = MaxHP;
	CurrentMP = MaxMP;
}

void AUnitBase::GoBackToOriginalLocation()
{
	AIUnitControler = Cast<AAIUnitController>(GetController());
	if(CombatComponent->IsRanged)
	{
		//AActor* ProjectStillSpawned = UGameplayStatics::GetActorOfClass(GetWorld(), ProjectileClass);

		if(AIUnitControler)
		{
			AIUnitControler->MoveToLocation(CombatComponent->BattlePositionTransform.GetTranslation(),1.f,false);
		}

	}else
	{
		if(AIUnitControler)
		{
			AIUnitControler->MoveToLocation(CombatComponent->BattlePositionTransform.GetTranslation(),1.f,false);
		}
	}
}
