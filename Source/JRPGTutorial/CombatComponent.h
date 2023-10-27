// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class AUnitBase;
class UActionCommands;
class ADynamicCamera;
class UUnitBattleHUD;
class AMagicBase;
class ADarkMagicaBase;
class ASupportMagicBase;

USTRUCT(BlueprintType)
struct FUnitStatModifier
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats")
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats")
	float MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats")
	float STR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats")
	float STA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats")
	float ACC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats")
	float HST;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStats")
	float WIS;

	FUnitStatModifier()
	{
		HP = 1;
		MP = 1;
		STR = 1;
		STA = 1;
		ACC = 1;
		HST = 1;
		WIS = 1;
	}
};

USTRUCT(BlueprintType)
struct FStatTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 HP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 STR;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 STA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ACC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 HST;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 WIS;
};

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class JRPGTUTORIAL_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// FUNCTIONS - Attack
	UFUNCTION(BlueprintNativeEvent, Category = "Attack")
	void AttackCommand(AUnitBase* Target);

	UFUNCTION(BlueprintNativeEvent, Category = "Attack")
	void MagicCommand(AUnitBase* Target, TSubclassOf<AMagicBase> MagicClassRef);

	//Physical attack
	UFUNCTION(BlueprintNativeEvent, Category = "PhysicalAttack")
	void MelleeAttack(AUnitBase* Target);

	UFUNCTION(BlueprintNativeEvent, Category = "PhysicalAttack")
	void RangedAttack(AUnitBase* Target);

	UFUNCTION(BlueprintNativeEvent, Category = "MagicAttack")
	void CastDarkAttack(AUnitBase* Target, TSubclassOf<AMagicBase> DarkMagicClass);

	UFUNCTION(BlueprintNativeEvent, Category = "MagicAttack")
	void CastSupportAttack(AUnitBase* Target, TSubclassOf<AMagicBase> SupportMagicClass);

	UPROPERTY()
	bool IsMagic = false;

	UPROPERTY()
	bool IsDarkMagic;

	UFUNCTION()
	FVector GetRangePositon(AUnitBase* Target);

	UFUNCTION()
	float CalculateDamage();

	UFUNCTION()
	float CalculateMagicDamage(TSubclassOf<AMagicBase> MagicBaseRef);

	// FUNCTIONS - Turn and Battle
	UFUNCTION(BlueprintCallable)
	void StartUnitTurn();

	UFUNCTION()
	void EndUnitTurn();

	UFUNCTION()
	void BeginBattle();

	UFUNCTION()
	void RequestTurn();

	// FUNCTIONS - Camera and Damage Calculation
	UFUNCTION()
	void SetDynamicCamera();

	UFUNCTION()
	float CalculateBaseDamage();

	UFUNCTION()
	float CalculateDamageResistance(float BaseDamage);

	// PROPERTIES - Ranged and Target
	UPROPERTY(EditAnywhere, Category = "Ranged Unit")
	bool IsRanged;

	UPROPERTY()
	AActor* TargetChoosed;

	// PROPERTIES - Unit Character and Stats
	UPROPERTY(BlueprintReadWrite)
	AUnitBase* UnitCharacter;

	UPROPERTY()
	FTransform BattlePositionTransform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UnitStats")
	class UDataTable* BaseStatTable;

	FStatTable* StatTable;

	UPROPERTY(EditAnywhere, Category = "UnitStats")
	FUnitStatModifier UnitStatModifier;

	// PROPERTIES - Controller and HUD Widget
	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	UUnitBattleHUD* UnitBattleHUD;

	UPROPERTY(EditAnywhere, Category = "Widget Classes")
	TSubclassOf<UUnitBattleHUD> UUnitBattleHUDClass;

	// PROPERTIES - Dynamic Camera and Timer Handle
	UPROPERTY()
	ADynamicCamera* DynamicCamera;

	UPROPERTY(EditAnywhere, Category = "Widget Classes")
	TSubclassOf<ADynamicCamera> DynamicCameraClass;

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle RequestTurnTimee;

	UPROPERTY()
	float HasteTime;

	// PROPERTIES - Magic Abilities
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<ADarkMagicaBase>> DarkMagicAbilities;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<ASupportMagicBase>> SupportMagicAbilities;

private:
	float MaxActionTime;
	float MinActionTime;
};
