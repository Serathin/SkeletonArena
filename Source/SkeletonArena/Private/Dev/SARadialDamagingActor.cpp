// Skeleton Arena. All Rights Reserved.


#include "Dev/SARadialDamagingActor.h"

#include <DrawDebugHelpers.h>
#include <Engine/EngineTypes.h>
#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>

// Sets default values
ASARadialDamagingActor::ASARadialDamagingActor()
:
sphere_radius_(300.f)
, sphere_color_(FColor::Green)
, damage_(10.f)
, damage_for_distance_(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	scene_component_ = CreateDefaultSubobject <USceneComponent>("Scene Component");
	SetRootComponent(scene_component_);
}

// Called when the game starts or when spawned
void ASARadialDamagingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASARadialDamagingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), sphere_radius_, 24, sphere_color_);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), damage_, GetActorLocation(), sphere_radius_, nullptr, {}, this, nullptr, !damage_for_distance_);
}

