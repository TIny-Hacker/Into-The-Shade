#include "ui.h"

#include <graphx.h>

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
    gfx_FillRectangle_NoClip(20, 20, 210, 200);
    gfx_SetColor(0);
    gfx_FillRectangle_NoClip(21, 21, 208, 198);
    gfx_SetColor(3);
    gfx_FillRectangle_NoClip(23, 23, 204, 194);
}