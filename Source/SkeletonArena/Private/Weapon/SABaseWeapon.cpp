// Skeleton Arena. All Rights Reserved.


#include "Weapon/SABaseWeapon.h"

#include <Components/SkeletalMeshComponent.h>

ASABaseWeapon::ASABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	skeletal_mesh_component_ = CreateDefaultSubobject <USkeletalMeshComponent> ("Skeletal Mesh Component");
	SetRootComponent(skeletal_mesh_component_);
}

void ASABaseWeapon::Fire()
{
  UE_LOG(LogTemp, Log, TEXT("F"));
}

void ASABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}
