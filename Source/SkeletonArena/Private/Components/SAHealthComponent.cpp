// Skeleton Arena. All Rights Reserved.


#include "Components/SAHealthComponent.h"

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
}
