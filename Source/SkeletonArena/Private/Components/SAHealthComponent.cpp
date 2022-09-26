// Skeleton Arena. All Rights Reserved.


#include "Components/SAHealthComponent.h"
#include <GameFramework/Actor.h>

#include "Dev/SAPoisonDamageType.h"
#include "Dev/SABleedingDamageType.h"

USAHealthComponent::USAHealthComponent()
:
max_health_(100.f)
, health_(max_health_)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USAHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	health_ = max_health_;

	if (AActor *owner = GetOwner()) owner->OnTakeAnyDamage.AddDynamic(this, &USAHealthComponent::OnTakeAnyDamage);
}

void USAHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	health_ = FMath::Clamp(health_ - Damage, 0.f, max_health_);
	if (DamageType)
	{
		if (DamageType->IsA <USAPoisonDamageType> ())
		{
			UE_LOG(LogTemp, Log, TEXT("Poison"));
		}
		else if (DamageType->IsA <USABleedingDamageType> ())
		{
			UE_LOG(LogTemp, Log, TEXT("Bleeding"));
		}
	}
}
