// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Weapon.generated.h"

class USceneComponent;
struct FDamageEvent;

USTRUCT()
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	// Called when the game starts or when spawned
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Settings")
	FVector FireOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Settings")
	float Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Settings")
	TSubclassOf<UDamageType> DamageTypeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Settings")
	float FireCooldown;

	FWeaponData()
	{
		FireOffset = FVector(0.0f, 0.0f, 0.0f);
		Damage = 10.0f;
		DamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FireCooldown = 0.5f;
	}
};

UCLASS()
class DEATHMATCHULTIMA_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Settings")
	FWeaponData WeaponConfig;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	FVector GetFireLocation() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	FRotator GetFireRotation() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	FVector GetFireDirection() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	bool IsHittingHurtable(FHitResult& HitResult) const;

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

	void DealDamage(float DamageAmount, AActor* Target);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

};
