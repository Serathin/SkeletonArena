// Skeleton Arena. All Rights Reserved.


#include "SABaseCharacter.h"

#include "SAMovementComponent.h"

// Sets default values
ASABaseCharacter::ASABaseCharacter(FObjectInitializer const &ObjectInitializer)
  :
Super(ObjectInitializer.SetDefaultSubobjectClass <USAMovementComponent> (CharacterMovementComponentName))
, bLShiftPressed(false)
, bIsForwardMoving(false)
{
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  SpringArmComponent = CreateDefaultSubobject <USpringArmComponent> ("Spring Arm Component");
  SpringArmComponent->SetupAttachment(GetRootComponent());
  SpringArmComponent->bUsePawnControlRotation = true;

  CameraComponent = CreateDefaultSubobject <UCameraComponent> ("Camera Component");
  CameraComponent->SetupAttachment(SpringArmComponent);

  if (USAMovementComponent *MovementComponent = dynamic_cast <USAMovementComponent *> (GetCharacterMovement()))
  {
    MovementComponent->OnRunningReq.BindUObject(this, &ASABaseCharacter::IsRunning);
  }
}

bool ASABaseCharacter::IsRunning() const
{
  return bIsForwardMoving && bLShiftPressed && !GetVelocity().IsZero();
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
  bIsForwardMoving = AxisValue > 0.f;
  AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ASABaseCharacter::MoveRight(float AxisValue)
{
  AddMovementInput(GetActorRightVector(), AxisValue);
}

void ASABaseCharacter::StartRunning()
{
  bLShiftPressed = true;
}

void ASABaseCharacter::StopRunning()
{
  bLShiftPressed = false;
}
