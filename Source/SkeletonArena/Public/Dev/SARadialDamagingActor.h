// Skeleton Arena. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SARadialDamagingActor.generated.h"

UCLASS()
class SKELETONARENA_API ASARadialDamagingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASARadialDamagingActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent *scene_component_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float sphere_radius_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor sphere_color_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damage_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool damage_for_distance_;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
