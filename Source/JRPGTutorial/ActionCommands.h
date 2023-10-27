// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionCommands.generated.h"

class UButton;
class AUnitBase;
class UTextBlock;

UCLASS()
class JRPGTUTORIAL_API UActionCommands : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized();

public: 

	UPROPERTY(BlueprintReadWrite)
	AUnitBase* Unit;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* UnitNameText;

//BUTTONS

	//Attack Button	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* AttackCommand;

	//Magic Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* MagicCommand;

	//Technique Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* TechniquesCommand;

	//Items Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ItemsCommand;
	
};