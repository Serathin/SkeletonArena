// Skeleton Arena. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SAHUD.generated.h"

/**
 * 
 */
UCLASS()
class SKELETONARENA_API ASAHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

private:
	void DrawCrosshair();
};
