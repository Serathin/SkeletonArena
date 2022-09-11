// Skeleton Arena. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SAMovementComponent.generated.h"

DECLARE_DELEGATE_RetVal(bool, OnRunningReq);

UCLASS()
class SKELETONARENA_API USAMovementComponent : public UCharacterMovementComponent
{
  GENERATED_BODY()

public:
  USAMovementComponent();
  
  virtual float GetMaxSpeed() const override;
  
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Running, meta = (ClampMin = 1.3f, ClampMax = 2.f))
  float VelocityMult;
  
  OnRunningReq OnRunningReq;
};
