// Skeleton Arena. All Rights Reserved.


#include "SABaseCharacter.h"

// Sets default values
ASABaseCharacter::ASABaseCharacter()
{
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  cameraComponent = CreateDefaultSubobject <UCameraComponent> ("Camera Component");
  cameraComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASABaseCharacter::BeginPlay()
{
  Super::BeginPlay();
}

// Called every frame
void ASABaseCharacter::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASABaseCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);
}
