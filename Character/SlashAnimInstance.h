#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SlashAnimInstance.generated.h"

class ASlash;
class UCharacterMovementComponent;

UCLASS()
class SOULSLIKE_API USlashAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	ASlash* Character;

	UPROPERTY(BlueprintReadWrite)
	UCharacterMovementComponent* CharacterMovement;

	UPROPERTY(BlueprintReadWrite)
	float GroundVelocity;

	UPROPERTY(BlueprintReadWrite)
	bool IsFalling;

	UPROPERTY(BlueprintReadWrite)
	float Zaxis;

};
