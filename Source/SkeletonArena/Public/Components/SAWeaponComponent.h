// Skeleton Arena. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAWeaponComponent.generated.h"

class ASABaseWeapon;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKELETONARENA_API USAWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USAWeaponComponent();

	void Fire();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
  	TSubclassOf <ASABaseWeapon> weapon_class_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName weapon_socket_name_;

private:
	void SpawnWeapon();

	UPROPERTY()
	ASABaseWeapon *current_weapon_;
};
