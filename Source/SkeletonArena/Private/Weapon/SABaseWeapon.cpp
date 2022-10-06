// Skeleton Arena. All Rights Reserved.


#include "Weapon/SABaseWeapon.h"

#include <Components/SkeletalMeshComponent.h>
#include <DrawDebugHelpers.h>
#include <GameFramework/Character.h>
#include <GameFramework/PlayerController.h>

ASABaseWeapon::ASABaseWeapon()
:
arrow_socket_name_("arrow1")
, line_trace_length_(1500.f)
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

	auto const player = Cast <ACharacter> (GetOwner());
	if (!player) return;

	auto const controller = player->GetController <APlayerController> ();
	if (!controller) return;

	FVector player_location;
	FRotator player_rotation;
	controller->GetPlayerViewPoint(player_location, player_rotation);

	FVector end_pos = player_location + player_rotation.Vector() * line_trace_length_;

	FTransform const socket_transform = skeletal_mesh_component_->GetSocketTransform(arrow_socket_name_);
	FVector const start_pos = socket_transform.GetLocation();

	FCollisionQueryParams collision_query_params;
	collision_query_params.AddIgnoredActor(player);

	FHitResult hit_result;
	GetWorld()->LineTraceSingleByChannel(hit_result, player_location, end_pos, ECollisionChannel::ECC_Visibility, collision_query_params);
	if (hit_result.bBlockingHit) end_pos = hit_result.ImpactPoint;

	GetWorld()->LineTraceSingleByChannel(hit_result, start_pos, end_pos, ECollisionChannel::ECC_Visibility, collision_query_params);
	if (hit_result.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), start_pos, hit_result.ImpactPoint, FColor::Red, false, 3.f, 0, 3.f);
		DrawDebugSphere(GetWorld(), hit_result.ImpactPoint, 10.f, 24, FColor::Red, false, 5.f);
	}
	else DrawDebugLine(GetWorld(), start_pos, end_pos, FColor::Red, false, 3.f, 0, 3.f);
}
