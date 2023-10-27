// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicBase.h"
#include "DarkMagicaBase.generated.h"

/**
 * 
 */
UCLASS()
class JRPGTUTORIAL_API ADarkMagicaBase : public AMagicBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageType> DamageTypeClass;

private:

	UFUNCTION()
	void DestroyProjectile();

	UFUNCTION()    
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
