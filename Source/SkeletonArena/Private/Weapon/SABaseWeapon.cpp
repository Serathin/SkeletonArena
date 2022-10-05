// Skeleton Arena. All Rights Reserved.


#include "Weapon/SABaseWeapon.h"

#include <Components/SkeletalMeshComponent.h>
#include <DrawDebugHelpers.h>

ASABaseWeapon::ASABaseWeapon()
:
arrow_socket_name_("arrow1")
, line_trace_length_(500.f)
{
	PrimaryActorTick.bCanEverTick = false;

	skeletal_mesh_component_ = CreateDefaultSubobject <USkeletalMeshComponent> ("Skeletal Mesh Component");
	SetRootComponent(skeletal_mesh_component_);
}

void ASABaseWeapon::Fire()
{
  MakeShot();
}

void ASABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(skeletal_mesh_component_);
}

void ASABaseWeapon::MakeShot()
{
	if (!GetWorld()) return;

	FTransform const socket_transform = skeletal_mesh_component_->GetSocketTransform(arrow_socket_name_);
	FVector const start_pos = socket_transform.GetLocation();
	FVector const direction = socket_transform.GetRotation().GetUpVector();
	FVector const end_pos = start_pos + direction * line_trace_length_;
	DrawDebugLine(GetWorld(), start_pos, end_pos, FColor::Red, false, 3.f, 0, 3.f);
}
