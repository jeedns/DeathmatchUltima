// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HitscanWeapon.h"
#include "KismetTraceUtils.h"

AHitscanWeapon::AHitscanWeapon()
{
	TraceColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);
	TraceHitColor = FLinearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void AHitscanWeapon::Fire()
{
	Super::Fire();
	if (GetLocalRole() == ROLE_Authority)
	{
		FVector Start = GetFireLocation();
		FVector End = (GetFireDirection() * TraceLength) + Start;
		TArray<FHitResult> Hits;
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(GetOwner());
		FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(Fire), true, GetOwner());

		bool bHit = GetWorld()->LineTraceMultiByObjectType(
			Hits,
			Start,
			End,
			TraceObjectTypes,
			TraceParams);
		for (int i = 0; i < Hits.Num(); i++)
		{
			FHitResult Hit = Hits[i];
			AActor* HitActor = Hit.GetActor();
			DealDamage(WeaponConfig.Damage, HitActor);
		}
		DrawDebugLineTraceMulti(GetWorld(), Start, End, DrawDebugType, bHit, Hits, TraceColor, TraceHitColor, DrawTime);
	}

	else
	{
		FVector Start = GetFireLocation();
		FVector End = (GetFireDirection() * TraceLength) + Start;
		TArray<FHitResult> Hits;
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(GetOwner());
		FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(Fire), true, GetOwner());

		bool bHit = GetWorld()->LineTraceMultiByObjectType(
			Hits,
			Start,
			End,
			TraceObjectTypes,
			TraceParams);

		DrawDebugLineTraceMulti(GetWorld(), Start, End, DrawDebugType, bHit, Hits, TraceColor, TraceHitColor, DrawTime);
	}
}

