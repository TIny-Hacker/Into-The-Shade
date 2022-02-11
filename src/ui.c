#include "ui.h"
#include "gfx/gfx.h"

#include <graphx.h>
#include <keypadc.h>

void ui_VerticalIndicator(int x, uint8_t y, uint8_t color, int fill) {
    gfx_SetColor(2);
    gfx_FillRectangle_NoClip(x, y, 20, 200);
    gfx_SetColor(0);
    gfx_FillRectangle_NoClip(x + 1, y + 1, 18, 198);
    gfx_SetColor(color);
    fill = fill * 194 / 100;
    y = y + (194 - fill);
    gfx_FillRectangle_NoClip(x + 3, y + 3, 14, fill);
}

void ui_BackgroundFrame(void) {
    gfx_FillScreen(17);
    gfx_SetColor(2);
    gfx_FillRectangle_NoClip(20, 18, 210, 200);
    gfx_SetColor(0);
    gfx_FillRectangle_NoClip(21, 19, 208, 198);
    gfx_SetColor(3);
    gfx_FillRectangle_NoClip(23, 21, 204, 194);
    gfx_ScaledTransparentSprite_NoClip(flame, 281, 219, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(stopwatch, 253, 219, 2, 2);
    gfx_SetTextScale(2, 2);
    gfx_PrintStringXY("Test Stage", 58, 222);   // Filler for level name

}

void ui_GameOver(void) {
    gfx_SetDrawBuffer();

    gfx_FillScreen(17);

    gfx_SetTextFGColor(0);
    gfx_PrintStringXY("Game Over!", 150, 100);  // I know it's off center but who cares

    gfx_BlitBuffer();

    while (!kb_IsDown(kb_KeyClear)) {
        kb_Scan();
    }
}

void ui_StageComplete(void) {
    gfx_SetDrawBuffer();

    gfx_FillScreen(17);

    gfx_SetTextFGColor(0);
    gfx_PrintStringXY("Complete!", 150, 100);

    gfx_BlitBuffer();

    while (!kb_IsDown(kb_KeyClear)) {
        kb_Scan();
    }
}