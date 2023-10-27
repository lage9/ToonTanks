// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TargetWindowSlot.generated.h"

class AUnitBase;
class AEnemyUnitBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetSelectionDelegate, AEnemyUnitBase*, SelectedEnemyUnit);

UCLASS()
class JRPGTUTORIAL_API UTargetWindowSlot : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

public:

	FTargetSelectionDelegate TargetSelectionDelegate;

	UFUNCTION(BlueprintCallable)
	void HandleTargetSelection();


	UPROPERTY(BlueprintReadWrite)
	AUnitBase* Unit;

// Target Button 

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* TargetSelectionButtom;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TargetNameText;

	
};
