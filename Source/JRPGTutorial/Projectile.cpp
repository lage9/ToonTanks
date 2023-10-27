// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "UnitBase.h"
#include "CombatComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereComponent;

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComp->ProjectileGravityScale = 0.f;
	ProjectileMovementComp->InitialSpeed = 3000.f;
	ProjectileMovementComp->MaxSpeed = 3000.f;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->IgnoreActorWhenMoving(GetInstigator(),true);
	SphereComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	InitialLifeSpan = 3.0f;
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::DestroyProjectile()
{
	Destroy();
}

void AProjectile::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEffect, this->GetTransform(),true,EPSCPoolMethod::None,true);
	AUnitBase* DamageCauser = Cast<AUnitBase>(GetInstigator());
	UCombatComponent* CombatComponent = Cast<UCombatComponent>(DamageCauser->CombatComponent);
 	AActor*	DamagedActor = CombatComponent->TargetChoosed;

	UGameplayStatics::ApplyDamage(DamagedActor,CombatComponent->CalculateDamage(),nullptr,Cast<AActor>(DamageCauser), DamageTypeClass);
	FTimerHandle DestroyProjectile;
	GetWorldTimerManager().SetTimer(DestroyProjectile,this, &AProjectile::DestroyProjectile, 0.2f,false);
}
