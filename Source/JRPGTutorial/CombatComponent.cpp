// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

//Character
#include "UnitBase.h"
#include "PartyUnitBase.h"

//Gameplay
#include "Kismet/GameplayStatics.h"
#include "BattleGameMode.h"
#include "Kismet/KismetMathLibrary.h"
#include "Containers/UnrealString.h"
#include "Engine/DataTable.h"
#include "UObject/Class.h"

//Widget
#include "Blueprint/UserWidget.h"
#include "ActionCommands.h"
#include "UnitBattleHUD.h"

//Camera
#include "DynamicCamera.h"
#include "TopDownCamera.h"

//AI
#include "AIUnitController.h"

//Magic
#include "MagicBase.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// load data table stats
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableStats(TEXT("/Script/Engine.DataTable'/Game/Blueprint/DataTable/BaseStatTable.BaseStatTable'"));
	if(DataTableStats.Succeeded())
	{
		BaseStatTable = DataTableStats.Object;
		UE_LOG(LogTemp, Error, TEXT("DATATABLESTATS SUCCEEDED"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("DATATABLESTATS DOES NOT SUCCEEDED"));
	}

}

// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	UnitCharacter = Cast<AUnitBase>(GetOwner());
	BattlePositionTransform = UnitCharacter->GetTransform();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);

	FName Level = FName(*FString::Printf(TEXT("%d"), UnitCharacter->UnitLevel));
	static const FString ContextString(TEXT("Data table context"));
	StatTable = BaseStatTable->FindRow<FStatTable>(Level, ContextString, true);

	if (UnitCharacter && StatTable)
    {
		UnitCharacter->SetMaxStats(UnitStatModifier.HP, UnitStatModifier.MP,StatTable->HP,StatTable->MP);
        UE_LOG(LogTemp, Warning, TEXT("UnitCharacter is valid: %s"), *UnitCharacter->GetName());
		BeginBattle();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("UnitCharacter is NULL"));
    }

}

// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

///Physical Attack
void UCombatComponent::AttackCommand_Implementation(AUnitBase* Target)
{
	if(UnitCharacter->GetClass()->IsChildOf<APartyUnitBase>())
	{
		Cast<ADynamicCamera>(PlayerController->GetViewTarget())->SetOrbit(false);
	}

	TargetChoosed = Cast<AActor>(Target);

	if(IsRanged)
	{
		RangedAttack_Implementation(Target);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ENEMY ATTACKING"));
		MelleeAttack_Implementation(Target);
	}	
	//TODO :: ADD ANIMATIONS TO MELLE AND CREATE THE RANGED ATTACK. WE ALREADY ADDED ANIMATION IN THE WIDGETS. basically create an evenet blueprintnative and create the animation in 
	// blueprint. then call the function in code  :D. ALSO WORK IN THE AI GOOD PROGRESS TODAY LOV U
}

//Magical Command
void UCombatComponent::MagicCommand_Implementation(AUnitBase* Target, TSubclassOf<AMagicBase> MagicClassRef)
{
	IsMagic = true;
	if(UnitCharacter->GetClass()->IsChildOf<APartyUnitBase>())
	{
		Cast<ADynamicCamera>(PlayerController->GetViewTarget())->SetOrbit(false);

		if(MagicClassRef->IsChildOf<ADarkMagicaBase>())
		{
			CastDarkAttack_Implementation(Target, MagicClassRef);
		}
		else
		{
			CastSupportAttack_Implementation(Target, MagicClassRef);
		}
	}
}

//Physical Attack
void UCombatComponent::MelleeAttack_Implementation(AUnitBase* Target)
{
	AAIUnitController* AIUnitControler = Cast<AAIUnitController>(Cast<AUnitBase>(GetOwner())->GetController());
	if(AIUnitControler)
	{
		if(UnitCharacter->GetClass()->IsChildOf<APartyUnitBase>())
		{
			if(UnitBattleHUD)
			{
				UnitBattleHUD->RemoveFromParent();
			}
		}
		UE_LOG(LogTemp, Error, TEXT("Move To Location"));
		EPathFollowingRequestResult::Type PathFollowingResult = AIUnitControler->MoveToActor(Target,200.f,false, true);	
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("No Controller"));
	}
}

void UCombatComponent::RangedAttack_Implementation(AUnitBase* Target)
{
	IsMagic = false;
	AAIUnitController* AIUnitControler = Cast<AAIUnitController>(Cast<AUnitBase>(GetOwner())->GetController());
	if(AIUnitControler)
	{
		if(UnitCharacter->GetClass()->IsChildOf<APartyUnitBase>())
		{
			if(UnitBattleHUD)
			{
				UnitBattleHUD->RemoveFromParent();
			}
		}
		AIUnitControler->MoveToLocation(GetRangePositon(Target),1.f,false, true);	
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("NO AI CONTROLER FOR RANGED?"));
	}
}

//Magic Attack
void UCombatComponent::CastDarkAttack_Implementation(AUnitBase* Target, TSubclassOf<AMagicBase> DarkMagicClass)
{
	IsDarkMagic = true;
	AAIUnitController* AIUnitControler = Cast<AAIUnitController>(Cast<AUnitBase>(GetOwner())->GetController());
	if(AIUnitControler)
	{
		if(UnitCharacter->GetClass()->IsChildOf<APartyUnitBase>())
		{
			if(UnitBattleHUD)
			{
				UnitBattleHUD->RemoveFromParent();
			}
		}
		AIUnitControler->MoveToLocation(GetRangePositon(Target),1.f,false, true);	
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("NO AI CONTROLER FOR RANGED?"));
	}
}

void UCombatComponent::CastSupportAttack_Implementation(AUnitBase* Target, TSubclassOf<AMagicBase> SupportMagicClass)
{
	IsDarkMagic = false;
	AAIUnitController* AIUnitControler = Cast<AAIUnitController>(Cast<AUnitBase>(GetOwner())->GetController());
	if(AIUnitControler)
	{
		if(UnitCharacter->GetClass()->IsChildOf<APartyUnitBase>())
		{
			if(UnitBattleHUD)
			{
				UnitBattleHUD->RemoveFromParent();
			}
		}
		AIUnitControler->MoveToLocation(GetRangePositon(Target),1.f,false, true);	
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("NO AI CONTROLER FOR RANGED?"));
	}
}


FVector UCombatComponent::GetRangePositon(AUnitBase *Target)
{
    FVector UnitLocation = UnitCharacter->GetActorLocation();
    FVector TargetLocation = Target->GetActorLocation();
    
    // Calculate the halfway point between UnitCharacter and Target
    FVector HalfwayPoint = UnitLocation  - (UnitLocation - TargetLocation) * 0.4f;

    // Adjust the Z-coordinate (assuming the movement should happen on the same Z-level)
    HalfwayPoint.Z = UnitLocation.Z;

    UE_LOG(LogTemp, Error, TEXT("RANGED ATTACK : %s"), *HalfwayPoint.ToString());

    return HalfwayPoint;
}

float UCombatComponent::CalculateDamage()
{
	return CalculateBaseDamage();
}

float UCombatComponent::CalculateMagicDamage(TSubclassOf<AMagicBase> MagicBaseRef)
{
	AMagicBase* MagicBaseDefault = Cast<AMagicBase>(MagicBaseRef->StaticClass());
	float WisdomParameter = UnitStatModifier.WIS * StatTable->WIS;
	float spellPowerDamage = (sqrt(MagicBaseDefault->SpellPowerTable[MagicBaseDefault->Rank])) * 2;
    return WisdomParameter * spellPowerDamage;
}

//Turn and Battle
void UCombatComponent::StartUnitTurn()
{
	if(UnitCharacter->GetClass()->IsChildOf<APartyUnitBase>())
	{
		if(UUnitBattleHUDClass)
		{
			UnitBattleHUD = Cast<UUnitBattleHUD>(CreateWidget(PlayerController, UUnitBattleHUDClass, EName::None));
			if(UnitBattleHUD)
			{
				UE_LOG(LogTemp, Error, TEXT("Unit Character start unit turn : %s"), *UnitCharacter->GetName());
				UnitBattleHUD->Unit = UnitCharacter;
				UnitBattleHUD->AddToViewport();
				UnitBattleHUD->TargetWindow->PartyUnit = UnitCharacter;
			}
		}
		SetDynamicCamera();
	}
	else
	{
		ABattleGameMode* GameMode = Cast<ABattleGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->SetTopDownCamera();
		int32 RandomAnimIndex = FMath::RandRange(0, GameMode->PartyArray.Num() - 1);
		AttackCommand_Implementation(Cast<AUnitBase>(GameMode->PartyArray[RandomAnimIndex]));
		UE_LOG(LogTemp, Error, TEXT("UUnitBattleHUDClass is None or is a Enemy class"));
	}
}

void UCombatComponent::EndUnitTurn()
{
	UE_LOG(LogTemp, Warning, TEXT("End Unit Turn Called"));
	Cast<ABattleGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->ReadyNextTurn();
}

void UCombatComponent::BeginBattle()
{

	if(BaseStatTable)
	{	
		if(StatTable)
		{
			float Haste = StatTable->HST * UnitStatModifier.HST;
			Haste = UKismetMathLibrary::NormalizeToRange(Haste,0.f,255.f);
			MaxActionTime = 3.f;
			MinActionTime = 1.f;
			HasteTime = ((1 - Haste) * (MaxActionTime - MinActionTime)) + MinActionTime;
			if(HasteTime <= 0)
			{
				HasteTime = 0.01f;
			}
			UnitCharacter->GetWorldTimerManager().SetTimer(RequestTurnTimee, this, &UCombatComponent::RequestTurn, HasteTime, false);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("NO LEVEL ATTRIBUTE DATA TABLE"));
		}
	}
}

void UCombatComponent::RequestTurn()
{
	if(Cast<ABattleGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		if(UnitCharacter)
		{
			UE_LOG(LogTemp, Warning, TEXT("REQUEST TURN CALLED"));
			Cast<ABattleGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->TurnRequest(UnitCharacter);
		}
	}
}

//Camera and Damage Calculation
void UCombatComponent::SetDynamicCamera()
{
	
	GetWorld()->SpawnActor<ADynamicCamera>();
	DynamicCamera = Cast<ADynamicCamera>(UGameplayStatics::GetActorOfClass(GetWorld(),DynamicCameraClass));

	if(DynamicCamera)
	{
		PlayerController->SetViewTargetWithBlend(DynamicCamera,0.f,VTBlend_Linear,0.f,false);
		DynamicCamera->SetLocation(UnitCharacter, FVector(0.f,0.f,0.f));
		Cast<ADynamicCamera>(PlayerController->GetViewTarget())->SetOrbit(true);
	}
}

float UCombatComponent::CalculateBaseDamage()
{
	float RandomParameter = FMath::RandRange(0.9f,1.1f);
	float CalculateDamage = ((UnitStatModifier.STR *  StatTable->STR) * 5) * RandomParameter;
	return CalculateDamage;
}

float UCombatComponent::CalculateDamageResistance(float BaseDamage)
{
	float StaminaParameter = UnitStatModifier.STA * StatTable->STA;
	float Resistance = FMath::Pow(BaseDamage,2.f) / (BaseDamage + StaminaParameter);
	return Resistance;
}
