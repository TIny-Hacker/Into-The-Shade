#include "ui.h"
#include "gfx/gfx.h"

#include <graphx.h>
#include <keypadc.h>

void ui_MainMenu(void) {
    gfx_FillScreen(17);
    gfx_SetColor(2);
    gfx_Rectangle_NoClip(21, 140, 49, 49);
    gfx_Rectangle_NoClip(78, 140, 49, 49);
    gfx_Rectangle_NoClip(135, 140, 49, 49);
    gfx_Rectangle_NoClip(192, 140, 49, 49);
    gfx_Rectangle_NoClip(249, 140, 49, 49);
    gfx_Rectangle_NoClip(108, 76, 92, 32);
    gfx_SetColor(0);
    gfx_Rectangle_NoClip(22, 141, 47, 47);
    gfx_Rectangle_NoClip(79, 141, 47, 47);
    gfx_Rectangle_NoClip(136, 141, 47, 47);
    gfx_Rectangle_NoClip(193, 141, 47, 47);
    gfx_Rectangle_NoClip(250, 141, 47, 47);
    gfx_Rectangle_NoClip(109, 77, 90, 30);
    gfx_SetColor(3);
    gfx_FillRectangle_NoClip(23, 142, 45, 45);
    gfx_FillRectangle_NoClip(80, 142, 45, 45);
    gfx_FillRectangle_NoClip(137, 142, 45, 45);
    gfx_FillRectangle_NoClip(194, 142, 45, 45);
    gfx_FillRectangle_NoClip(251, 142, 45, 45);
    gfx_FillRectangle_NoClip(110, 78, 88, 28);

    gfx_SetTextScale(3, 3);
    gfx_PrintStringXY("Into the Shade", 7, 20);
    gfx_PrintStringXY("Play", 112, 80);

    gfx_ScaledTransparentSprite_NoClip(greenCarRight, 29, 149, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(brownCarRight, 86, 149, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(motorcycleRight, 143, 149, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(redCarRight, 200, 149, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(truckRight, 261, 149, 2, 2);
}

void ui_CarPicked(uint16_t x, uint8_t y, uint8_t carType, gfx_sprite_t **carRight) {
    gfx_SetColor(2);
    gfx_Rectangle_NoClip(x, y, 32, 32);
    gfx_SetColor(0);
    gfx_Rectangle_NoClip(x + 1, y + 1, 30, 30);
    gfx_SetColor(3);
    gfx_FillRectangle_NoClip(x + 2, y + 2, 28, 28);
    gfx_TransparentSprite_NoClip(carRight[carType], x + 8, y + 8);
}

void ui_Cursor(uint16_t color, uint16_t cursorX, uint8_t cursorY) {
    gfx_SetColor(color);
    if (cursorY == 75) {
        gfx_Rectangle_NoClip(cursorX, cursorY, 94, 34);
    } else {
        gfx_Rectangle_NoClip(cursorX, cursorY, 51, 51);
    }
}

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