// Skeleton Arena. All Rights Reserved.


#include "Components/SAHealthComponent.h"
#include <GameFramework/Actor.h>
#include <Engine/World.h>
#include <TimerManager.h>

#include "Dev/SAPoisonDamageType.h"
#include "Dev/SABleedingDamageType.h"

USAHealthComponent::USAHealthComponent()
:
max_health_(100.f)
, auto_heal_enabled_(true)
, auto_heal_delay_(2.f)
, auto_heal_update_frequency_(0.3f)
, auto_heal_amount_(1.f)
, health_(max_health_)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USAHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(max_health_);

	if (AActor *owner = GetOwner()) owner->OnTakeAnyDamage.AddDynamic(this, &USAHealthComponent::OnTakeAnyDamage);
}

void USAHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage < 0.f || IsDead() || !GetWorld()) return;
	SetHealth(health_ - Damage);
	GetWorld()->GetTimerManager().ClearTimer(auto_heal_timer_);
	if (IsDead()) on_death_.Broadcast();
	else if (auto_heal_enabled_) GetWorld()->GetTimerManager().SetTimer(auto_heal_timer_, this, &USAHealthComponent::AutoHeal, auto_heal_update_frequency_, true, auto_heal_delay_);
}

void USAHealthComponent::AutoHeal()
{
	if (!IsDead()) SetHealth(health_ + auto_heal_amount_);
}

void USAHealthComponent::SetHealth(float health)
{
	health_ = FMath::Clamp(health, 0.f, max_health_);
	on_health_changed_.Broadcast(health_);
	if (FMath::IsNearlyEqual(health_, max_health_) && GetWorld()) GetWorld()->GetTimerManager().ClearTimer(auto_heal_timer_);
}
