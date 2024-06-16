// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Weapon.generated.h"

class USceneComponent;

UCLASS()
class DEATHMATCHULTIMA_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	UPROPERTY(BlueprintReadWrite, Category = "Weapon Settings", Meta = (ExposeOnSpawn = true))
	USceneComponent* FireOriginComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Settings")
	float FireCooldown;

	bool bWantsToFire;
	
	bool bIsCoolingdown;
	
	FTimerHandle TimerHandle_FireCooldown;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, reliable, server, WithValidation)
	void ServerStartFire();
	
	UFUNCTION(BlueprintCallable, reliable, server, WithValidation)
	void ServerStopFire();

	void TryFire();

	// [local + server] weapon specific fire implementation
	virtual void Fire();

	void OnCooldownFinished();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

};
