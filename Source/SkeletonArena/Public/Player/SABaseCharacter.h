// Skeleton Arena. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "SABaseCharacter.generated.h"

UCLASS()
class SKELETONARENA_API ASABaseCharacter : public ACharacter
{
  GENERATED_BODY()

public:
  // Sets default values for this character's properties
  ASABaseCharacter();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  UPROPERTY(VisibleAnywhere, Category = Components)
  UCameraComponent *cameraComponent;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
};
