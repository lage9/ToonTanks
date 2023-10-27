// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicBase.generated.h"

class UTextBlock;

UCLASS()
class JRPGTUTORIAL_API AMagicBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditDefaultsOnly, Category = "Default")
	FText MagicName = FText::FromString(TEXT("DefaultMagicName"));

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	int32 Rank;

	UPROPERTY()
	AUnitBase* SpellTarget;

	UPROPERTY()
	TMap<int32, float> SpellPowerTable;

	UPROPERTY()
	TMap<int32, float> ManaCostTable;

};
