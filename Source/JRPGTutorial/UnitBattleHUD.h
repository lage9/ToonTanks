// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitBattleHUD.generated.h"

class UActionCommands;
class UTargetWindow;
class AUnitBase;
class UMagicWindow;

UCLASS()
class JRPGTUTORIAL_API UUnitBattleHUD : public UUserWidget
{
	GENERATED_BODY()

protected:

virtual void NativeConstruct() override;

public:

	UPROPERTY(BlueprintReadWrite)
	AUnitBase* Unit;

	//ActionCommands Widget
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UActionCommands* ActionCommands;

	//PartyCommands Widget
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTargetWindow* TargetWindow;

	//MagicCommands Widget
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UMagicWindow* MagicWindow;

//BUTTONS BINDINGS

	UFUNCTION()
	void OnAttackCommand();

	UFUNCTION()
	void OnMagicCommand();
	
	UFUNCTION()
	void OnTechniquesCommand();

	UFUNCTION()
	void OnItemsCommand();

	UFUNCTION()
	void BackTargetCommand();

	UFUNCTION()
	void BackMagicCommand();

	UFUNCTION()
	void AbilityChosen(TSubclassOf<AMagicBase> ChosenMagic);

//Animation Function

	UFUNCTION(BlueprintImplementableEvent, Category = "Animations")
	void ShowTargetAnimation();

	UFUNCTION(BlueprintImplementableEvent, Category = "Animations")
	void BackTargetAnimation();

	UFUNCTION(BlueprintImplementableEvent, Category = "Animations")
	void ShowMagicAnimation();

	UFUNCTION(BlueprintImplementableEvent, Category = "Animations")
	void BackMagicAnimation();
};
