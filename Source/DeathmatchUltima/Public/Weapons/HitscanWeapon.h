// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HitscanWeapon.generated.h"

/**
 * 
 */
UCLASS(Abstract)

class DEATHMATCHULTIMA_API AHitscanWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	AHitscanWeapon();
	
protected:
	virtual void Fire() override;

	UPROPERTY(EditDefaultsOnly, Category = "Hitscan Settings")
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

	UPROPERTY(EditDefaultsOnly, Category = "Hitscan Settings")
	float TraceLength = 5000.0f;

	UPROPERTY(EditAnywhere, Category = "Debugs")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType = EDrawDebugTrace::ForDuration;

	UPROPERTY(EditAnywhere, Category = "Debugs")
	FLinearColor TraceColor;

	UPROPERTY(EditAnywhere, Category = "Debugs")
	FLinearColor TraceHitColor;

	UPROPERTY(EditAnywhere, Category = "Debugs")
	float DrawTime = 5.0f;  
};
