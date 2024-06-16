// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon.h"
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

void AWeapon::StartFire()
{
	bWantsToFire = true;
	if (!bIsCoolingdown)
	{
		 ServerStartFire();
	}
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
	
	if (FireCooldown <= 0.0f)
	{
		bIsCoolingdown = false;
	}

	else
	{
		GetWorldTimerManager().SetTimer(TimerHandle_FireCooldown, this, &AWeapon::OnCooldownFinished, FireCooldown, false);
	}
}

void AWeapon::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("Fire"));
}

void AWeapon::OnCooldownFinished()
{
	bIsCoolingdown = false;
	if (!bWantsToFire) return;
	TryFire();
}


