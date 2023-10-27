// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PartyWidgetSlot.generated.h"

class AUnitBase;
class UProgressBar;
class UTextBlock;


UCLASS()
class JRPGTUTORIAL_API UPartyWidgetSlot : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
public:


//FUNCTIONS

	UFUNCTION()
	void SetCharacterActionBar();

	UFUNCTION()
	void HandleDamage(float DamageTaken, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser);

	UFUNCTION()
	void SetBeginBattleStats();

//PROPERTIES




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	AUnitBase* Unit;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UProgressBar* CharacterActionBar;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UTextBlock* UnitNameText;

	bool DoOnce = true;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UTextBlock* HPNameText;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UTextBlock* HPMaxText;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UTextBlock* HPCurrentText;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UTextBlock* MPNameText;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UTextBlock* MPCurrentText;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UTextBlock* MPMaxText;

	float LerpSpeed;
	float PercentBar;

	/// CREATE A BAR HERE AND CREATE THE FUNCTION TO MAKE IT SMOOTH HEHEHEHEHEH

};
