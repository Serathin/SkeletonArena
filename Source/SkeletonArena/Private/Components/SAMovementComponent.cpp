// Skeleton Arena. All Rights Reserved.


#include "Components/SAMovementComponent.h"

USAMovementComponent::USAMovementComponent()
  :
VelocityMult(1.5f)
{
  
}


float USAMovementComponent::GetMaxSpeed() const
{
  float const MaxSpeed = Super::GetMaxSpeed();
  return OnRunningReq.Execute() ? MaxSpeed * VelocityMult : MaxSpeed;
}
