// Skeleton Arena. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "SABaseCharacter.generated.h"

class USAHealthComponent;
class UTextRenderComponent;
class UAnimMontage;

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

  UFUNCTION()
  void DamageOnLanded(FHitResult const &hit_result);

  UPROPERTY(VisibleAnywhere, Category = Components)
  USpringArmComponent *spring_arm_component_;

  UPROPERTY(VisibleAnywhere, Category = Components)
  UCameraComponent *camera_component_;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
  USAHealthComponent *health_component_;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
  UTextRenderComponent *health_render_component_;

  UPROPERTY(EditDefaultsOnly)
  UAnimMontage *death_anim_montage_;

  UPROPERTY(BlueprintReadOnly)
  bool lshift_pressed_;

  UPROPERTY(BlueprintReadOnly)
  bool is_forward_moving_;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = LandedDamage)
  FVector2D landed_damage_min_max_;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = LandedDamage)
  FVector2D landed_damage_velocity_min_max_;

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

  void OnHealthChanged(float health);
  void OnDeath();
};
