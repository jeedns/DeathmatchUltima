// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HitscanWeapon.h"
#include "KismetTraceUtils.h"

AHitscanWeapon::AHitscanWeapon()
{

}
void AHitscanWeapon::Fire()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		FVector Start = FireOriginComponent->GetComponentLocation();
		FVector End = (FireOriginComponent->GetForwardVector() * TraceLength) + FireOriginComponent->GetComponentLocation();
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

