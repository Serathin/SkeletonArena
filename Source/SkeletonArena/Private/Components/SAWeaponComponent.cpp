// Skeleton Arena. All Rights Reserved.


#include "Components/SAWeaponComponent.h"

#include <GameFramework/Character.h>
#include <Components/SkeletalMeshComponent.h>

#include "SABaseWeapon.h"


USAWeaponComponent::USAWeaponComponent()
:
weapon_socket_name_("hand_rSocket")
, current_weapon_(nullptr)
{
  PrimaryComponentTick.bCanEverTick = false;
}

void USAWeaponComponent::Fire()
{
	if (!current_weapon_) return;
	current_weapon_->Fire();
}

void USAWeaponComponent::BeginPlay()
{
  Super::BeginPlay();

  SpawnWeapon();
}

void USAWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
  Super::EndPlay(EndPlayReason);

  if (current_weapon_) current_weapon_->Destroy();
}


void USAWeaponComponent::SpawnWeapon()
{
  if (GetWorld())
  {
    if (auto owner = Cast <ACharacter> (GetOwner()))
    {
	    if ((current_weapon_ = GetWorld()->SpawnActor <ASABaseWeapon> (weapon_class_)) != nullptr)
	    {
		    FAttachmentTransformRules attachment_transform_rules(EAttachmentRule::SnapToTarget, false);
        current_weapon_->AttachToComponent(owner->GetMesh(), attachment_transform_rules, weapon_socket_name_);
        current_weapon_->SetOwner(owner);
	    }
    }
  }
}
