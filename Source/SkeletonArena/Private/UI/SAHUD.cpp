// Skeleton Arena. All Rights Reserved.


#include "UI/SAHUD.h"
#include <GameFramework/HUD.h>
#include <Engine/Canvas.h>
#include <Math/Color.h>

void ASAHUD::DrawHUD()
{
    Super::DrawHUD();

    DrawCrosshair();
}

void ASAHUD::DrawCrosshair()
{
    TInterval <float> const center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    float const half_line_size = 10.f;
    float const line_thickness = 2.f;
    FLinearColor const line_color(FLinearColor::Green);

    DrawLine(center.Min - half_line_size, center.Max, center.Min + half_line_size, center.Max, line_color, line_thickness);
    DrawLine(center.Min, center.Max - half_line_size, center.Min, center.Max + half_line_size, line_color, line_thickness);
}
