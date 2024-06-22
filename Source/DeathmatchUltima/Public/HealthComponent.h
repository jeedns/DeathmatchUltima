// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthChangeDelegate, float, NewHealth);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )


class DEATHMATCHULTIMA_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(ReplicatedUsing = OnRep_Health)
	float Health;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float InitialHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth = 100.0f;

	void SetHealth(float NewHealth);

	UFUNCTION()
	void OnRep_Health();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeHeal(float HealAmount, class AController* InstigatedBy, AActor* HealCauser);

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float DamageAmount, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintPure, Category = "Health")
	bool IsDead() const;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth() const { return Health; }
		
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetMaxHealth() const { return MaxHealth; }

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FDeathDelegate OnDied;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FHealthChangeDelegate OnHealthChanged;
};
