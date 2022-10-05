// Skeleton Arena. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SABaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SKELETONARENA_API ASABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	ASABaseWeapon();

	virtual void Fire();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent *skeletal_mesh_component_;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName arrow_socket_name_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float line_trace_length_;

private:
	void MakeShot();
};
