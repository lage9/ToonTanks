// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MagicWindowSlot.generated.h"

class UButton;
class UTextBlock;
class AMagicBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityChosen, TSubclassOf<AMagicBase>, Ability);

UCLASS()
class JRPGTUTORIAL_API UMagicWindowSlot : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

public:

	UPROPERTY()
	TSubclassOf<AMagicBase> MagicBaseClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* MagicSelectionButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MagicNameText;

	UFUNCTION()
	void OnMagicSelectionButton();

	FAbilityChosen AbilityChosenDelegate;
	
};
