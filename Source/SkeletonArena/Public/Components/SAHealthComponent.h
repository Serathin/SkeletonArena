// Skeleton Arena. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKELETONARENA_API USAHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USAHealthComponent();

	float GetHealth() const { return health_; }
	bool IsDead() const { return FMath::IsNearlyZero(health_); }

	FOnDeath on_death_;
	FOnHealthChanged on_health_changed_;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0.f, ClampMax = 1000000.f))
	float max_health_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AutoHeal)
	bool auto_heal_enabled_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AutoHeal, meta = (ClampMin = 0.f, EditCondition = auto_heal_enabled_))
	float auto_heal_delay_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AutoHeal, meta = (ClampMin = 0.f, EditCondition = auto_heal_enabled_))
	float auto_heal_update_frequency_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AutoHeal, meta = (ClampMin = 0.f, EditCondition = auto_heal_enabled_))
	float auto_heal_amount_;

private:
	UFUNCTION()
  	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void AutoHeal();
	void SetHealth(float health);

	float health_;

	FTimerHandle auto_heal_timer_;
};
