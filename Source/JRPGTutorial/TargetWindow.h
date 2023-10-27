// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TargetWindow.generated.h"

class UScrollBox;
class ABattleGameMode;
class UTargetWindowSlot;
class UButton;
class AUnitBase;
class AEnemyUnitBase;
class AMagicBase;


UCLASS()
class JRPGTUTORIAL_API UTargetWindow : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

public:

	UFUNCTION(BlueprintCallable)
	void OnTargetSelected(AEnemyUnitBase* SelectedEnemyUnit);

	UPROPERTY()
	TSubclassOf<AMagicBase> MagicBaseRef;

	UPROPERTY()
	AUnitBase* PartyUnit;

//BUTTON

	UFUNCTION()
	void OnTargetSelectionButton(AEnemyUnitBase* SelectedEnemyUnit);

	UPROPERTY()
	ABattleGameMode* BattleGameMode;

//Widget Components

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* TargetList;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BackCommand;

	UFUNCTION()
	void PopulateTargetList();
	
//Target Widget Slot

	UPROPERTY(EditAnywhere, Category = "Blueprint Classes")
	TSubclassOf<UTargetWindowSlot> TargetWindowSlotClass;
	
};
