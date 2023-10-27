// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UnitBase.generated.h"

class UCombatComponent;
class AAIUnitController;
class AEnemyUnitBase;
class AProjectile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FDamageDelegate, float, DamageAmount, FDamageEvent const&, DamageEvent, AController*, InstigatedBy, AActor*, DamageCauser);

UCLASS()
class JRPGTUTORIAL_API AUnitBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnitBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

// Damage

	FDamageDelegate OnUnitTakeDamage;

	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent,class AController * EventInstigator,AActor * DamageCauser) override;

//ANIMATION

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations Hit")
	UAnimMontage* HitMontage;

	UFUNCTION()
	float PlayMelleeAttackMontage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAttack")
	TArray<UAnimMontage*> MeleeAttackMontage;

	UFUNCTION()
	float PlayRangedAttackMontage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RangedAttack")
	TArray<UAnimMontage*> RangedAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MagicAttack")
	TArray<UAnimMontage*> DarkMagicAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MagicAttack")
	TArray<UAnimMontage*> SupportMagicAttackMontage;

	UPROPERTY(EditAnywhere, Category = "RangedAttack")
	TSubclassOf<AProjectile> ProjectileClass;

	UFUNCTION()
	float PlayDarkMagicMontage();

	UFUNCTION()
	float PlaySupportMagicMontage();
	
	UPROPERTY(EditAnywhere, Category = "DarkMagicAttack")
	TSubclassOf<ADarkMagicaBase> DarkMagicClass;

	UPROPERTY(EditAnywhere, Category = "SupportMagicAttack")
	TSubclassOf<ASupportMagicBase> SupportMagicClass;

	UFUNCTION()
	void AdjustRotation();

	UFUNCTION()
	void SetMaxStats(float HP, float MP,int32 IntHP, int32 IntMP);


//PROPERTIES

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UCombatComponent* CombatComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 UnitLevel;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText Name = FText::FromString("Default");

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CurrentHP;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHP;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CurrentMP;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxMP;

	UPROPERTY()
	int32 BasePhysicalDamage;

//AI MOVEMENT

	UPROPERTY()
	AAIUnitController* AIUnitControler;

	UFUNCTION()
	void GoBackToOriginalLocation();
};
