// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon.h"
#include "Engine/DamageEvents.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
	bWantsToFire = false;
	bIsCoolingdown = false;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AWeapon::GetFireLocation() const
{
	FVector FireLocation;
	FRotator FireRotation;
	GetInstigatorController()->GetPlayerViewPoint(FireLocation, FireRotation);
	return FireLocation;
}

FRotator AWeapon::GetFireRotation() const
{
	FVector FireLocation;
	FRotator FireRotation;
	GetInstigatorController()->GetPlayerViewPoint(FireLocation, FireRotation);
	return FireRotation;
}

FVector AWeapon::GetFireDirection() const
{
	FVector FireLocation;
	FRotator FireRotation;
	GetInstigatorController()->GetPlayerViewPoint(FireLocation, FireRotation);
	return FireRotation.Vector();
}

bool AWeapon::IsHittingHurtable(FHitResult& HitResult) const
{
	return HitResult.bBlockingHit;
}

void AWeapon::StartFire()
{
	bWantsToFire = true;
	ServerStartFire();
	TryFire();
}

void AWeapon::StopFire()
{
	bWantsToFire = false;
	ServerStopFire();
}

bool AWeapon::ServerStartFire_Validate()
{
	return true;
}

void AWeapon::ServerStartFire_Implementation()
{
	bWantsToFire = true;
	TryFire();
}

bool AWeapon::ServerStopFire_Validate()
{
	return true;
}

void AWeapon::ServerStopFire_Implementation()
{
	bWantsToFire = false; 
}

void AWeapon::TryFire()
{
	if (bIsCoolingdown) return;
	Fire();
	bIsCoolingdown = true;		
	
	if (WeaponConfig.FireCooldown <= 0.0f)
	{
		bIsCoolingdown = false;
	}

	else
	{
		GetWorldTimerManager().SetTimer(TimerHandle_FireCooldown, this, &AWeapon::OnCooldownFinished, WeaponConfig.FireCooldown, false);
	}
}

void AWeapon::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("Fire"));
}

void AWeapon::OnCooldownFinished()
{
	bIsCoolingdown = false;
	if (bWantsToFire)
	{
		TryFire();
	}
}

void AWeapon::DealDamage(float DamageAmount, AActor* Target)
{
	FDamageEvent DamageEvent(WeaponConfig.DamageTypeClass);
	Target->TakeDamage(WeaponConfig.Damage, DamageEvent, GetInstigatorController(), this);
}


