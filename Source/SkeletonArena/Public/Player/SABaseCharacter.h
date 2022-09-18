// Skeleton Arena. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "SABaseCharacter.generated.h"

UCLASS()
class SKELETONARENA_API ASABaseCharacter : public ACharacter
{
  GENERATED_BODY()

public:
  // Sets default values for this character's properties
  ASABaseCharacter(FObjectInitializer const &ObjectInitializer);

  UFUNCTION(BlueprintCallable)
  bool IsRunning() const;
  UFUNCTION(BlueprintCallable)
  float GetDirection() const;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  UPROPERTY(VisibleAnywhere, Category = Components)
  USpringArmComponent *SpringArmComponent;

  UPROPERTY(VisibleAnywhere, Category = Components)
  UCameraComponent *CameraComponent;

  UPROPERTY(BlueprintReadOnly)
  bool bLShiftPressed;

  UPROPERTY(BlueprintReadOnly)
  bool bIsForwardMoving;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

private:
  void MoveForward(float AxisValue);
  void MoveRight(float AxisValue);

  void StartRunning();
  void StopRunning();
};
