// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicBase.h"
#include "Components/TextBlock.h"

// Sets default values
AMagicBase::AMagicBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpellPowerTable.Add(1,12.f);
	SpellPowerTable.Add(2,24.f);
	SpellPowerTable.Add(3,36.f);

	ManaCostTable.Add(1,6.f);
	ManaCostTable.Add(1,14.f);
	ManaCostTable.Add(3,24.f);
}

// Called when the game starts or when spawned
void AMagicBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagicBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

