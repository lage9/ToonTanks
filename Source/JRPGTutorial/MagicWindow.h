// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MagicWindow.generated.h"

class UButton;
class UScrollBox;
class UMagicWindowSlot;
class UWidgetSwitcher;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityChosenTarget, TSubclassOf<AMagicBase>, Ability);


UCLASS()
class JRPGTUTORIAL_API UMagicWindow : public UUserWidget
{
	GENERATED_BODY()


protected:

	virtual void NativeConstruct() override;

public:

	UPROPERTY()
	AUnitBase* PartyUnit;

	UPROPERTY()
	ABattleGameMode* BattleGameMode;

//Widget Components

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidgetSwitcher* MagicMenuSwitcher;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* DarkMagicCommand;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SupportMagicCommand;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* MagicList;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BackCommand;

	
//FUNCTIONS

	UFUNCTION()
	void OnDarkMagicCommand();

	UFUNCTION()
	void OnSupportMagicCommand();

	UFUNCTION()
	void AbilityChosen(TSubclassOf<AMagicBase> ChosenMagic);

	FAbilityChosenTarget AbilityChosenTargetDelegate;
	
//Target Widget Slot

	UPROPERTY(EditAnywhere, Category = "Blueprint Classes")
	TSubclassOf<UMagicWindowSlot> MagicWindowSlotClass;
};
