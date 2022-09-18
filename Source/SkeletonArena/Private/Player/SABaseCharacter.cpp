// Skeleton Arena. All Rights Reserved.


#include "SABaseCharacter.h"

#include <Components/InputComponent.h>
#include <Components/TextRenderComponent.h>

#include "Math/UnrealMathUtility.h"
#include "SAMovementComponent.h"
#include "SAHealthComponent.h"

// Sets default values
ASABaseCharacter::ASABaseCharacter(FObjectInitializer const &ObjectInitializer)
:
Super(ObjectInitializer.SetDefaultSubobjectClass <USAMovementComponent> (CharacterMovementComponentName))
, lshift_pressed_(false)
, is_forward_moving_(false)
{
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  spring_arm_component_ = CreateDefaultSubobject <USpringArmComponent> ("Spring Arm Component");
  spring_arm_component_->SetupAttachment(GetRootComponent());
  spring_arm_component_->bUsePawnControlRotation = true;

  camera_component_ = CreateDefaultSubobject <UCameraComponent> ("Camera Component");
  camera_component_->SetupAttachment(spring_arm_component_);

  health_component_ = CreateDefaultSubobject <USAHealthComponent> ("Health Component");

  health_render_component_ = CreateDefaultSubobject <UTextRenderComponent> ("Health Render Component");
  health_render_component_->SetupAttachment(GetRootComponent());

  if (USAMovementComponent *MovementComponent = dynamic_cast <USAMovementComponent *> (GetCharacterMovement()))
  {
    MovementComponent->OnRunningReq.BindUObject(this, &ASABaseCharacter::IsRunning);
  }
}

bool ASABaseCharacter::IsRunning() const
{
  return is_forward_moving_ && lshift_pressed_ && !GetVelocity().IsZero();
}

float ASABaseCharacter::GetDirection() const
{
  if (GetVelocity().IsZero()) return 0.f;
  FVector const forward_vector = GetActorForwardVector();
  FVector const velocity = GetVelocity().GetSafeNormal();
  FVector const cross_product = FVector::CrossProduct(forward_vector, velocity);
  float const dot_product = FVector::DotProduct(forward_vector, velocity);
  float const angle = FMath::RadiansToDegrees(FMath::Acos(dot_product));
  
  return cross_product.IsZero() ? angle : angle * FMath::Sign(cross_product.Z);
}


// Called when the game starts or when spawned
void ASABaseCharacter::BeginPlay()
{
  Super::BeginPlay();

  check(health_component_);
  check(health_render_component_);
}

// Called every frame
void ASABaseCharacter::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  float const health = health_component_->GetHealth();
  health_render_component_->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), health)));
}

// Called to bind functionality to input
void ASABaseCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);
  
  PlayerInputComponent->BindAxis("MoveForward", this, &ASABaseCharacter::MoveForward);
  PlayerInputComponent->BindAxis("MoveRight", this, &ASABaseCharacter::MoveRight);
  PlayerInputComponent->BindAxis("LookUp", this, &ASABaseCharacter::AddControllerPitchInput);
  PlayerInputComponent->BindAxis("TurnAround", this, &ASABaseCharacter::AddControllerYawInput);

  PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASABaseCharacter::Jump);
  PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASABaseCharacter::StartRunning);
  PlayerInputComponent->BindAction("Run", IE_Released, this, &ASABaseCharacter::StopRunning);
}

void ASABaseCharacter::MoveForward(float AxisValue)
{
  is_forward_moving_ = AxisValue > 0.f;
  if (AxisValue == 0.f) return;
  AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ASABaseCharacter::MoveRight(float AxisValue)
{
  if (AxisValue == 0.f) return;
  AddMovementInput(GetActorRightVector(), AxisValue);
}

void ASABaseCharacter::StartRunning()
{
  lshift_pressed_ = true;
}

void ASABaseCharacter::StopRunning()
{
  lshift_pressed_ = false;
}
