#include "ui.h"

#include <graphx.h>

void ui_verticalIndicator(int x, uint8_t y, uint8_t color, int fill) {
    gfx_SetColor(2);
    gfx_FillRectangle_NoClip(x, y, 20, 200);
    gfx_SetColor(0);
    gfx_FillRectangle_NoClip(x + 1, y + 1, 18, 198);
    gfx_SetColor(color);
    fill = fill * 194 / 100;
    y = y + (194 - fill);
    gfx_FillRectangle_NoClip(x + 3, y + 3, 14, fill);
}