// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DealDamageNotify.generated.h"

class AUnitBase;

UCLASS()
class JRPGTUTORIAL_API UDealDamageNotify : public UAnimNotify
{
	GENERATED_BODY()


	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageType> DamageTypeClass;

};
