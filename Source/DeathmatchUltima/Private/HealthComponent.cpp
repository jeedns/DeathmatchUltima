// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Net/UnrealNetwork.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealthComponent::OnTakeAnyDamage);
	if (GetOwner()->HasAuthority())
	{
		SetHealth(InitialHealth);
	}
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::SetHealth(float NewHealth)
{
	if (NewHealth != Health)                            
	{
		Health = NewHealth;
		Health = FMath::Clamp(Health, 0.0f, MaxHealth);
		OnRep_Health();
		if (IsDead())
		{
			OnDied.Broadcast();
		}
	}
}

void UHealthComponent::OnRep_Health()
{
	OnHealthChanged.Broadcast(Health);
}


void UHealthComponent::TakeHeal(float HealAmount, class AController* InstigatedBy, AActor* HealCauser)
{
	if (GetOwner()->HasAuthority())
	{
		SetHealth(Health + HealAmount);
	}
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float DamageAmount, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	SetHealth(Health - DamageAmount);
}

bool UHealthComponent::IsDead() const
{
	return Health == 0.0f;
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	DOREPLIFETIME(UHealthComponent, Health);
}

