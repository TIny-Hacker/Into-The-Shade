#include "gfx/gfx.h"

#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <stdbool.h>

void car(x, y, direction) {
    gfx_SetDrawBuffer();

    gfx_FillScreen(2);

    switch (direction) {
        case 0:
            gfx_ScaledTransparentSprite_NoClip(greenCarRight, x, y, 3, 3);
            break;
        case 1:
            gfx_ScaledTransparentSprite_NoClip(greenCarLeft, x, y, 3, 3);
            break;
        case 2:
            gfx_ScaledSprite_NoClip(greenCarDown, x, y, 3, 3);
            break;
        case 3:
            gfx_ScaledSprite_NoClip(greenCarUp, x, y, 3, 3);
            break;
        default:
            break;
    }

    gfx_BlitBuffer();
    gfx_SetDrawScreen();
}

int main(void) {
    gfx_Begin();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetTransparentColor(1);

    uint8_t y = 4;
    int x = 4;
    uint8_t direction = 0;

    car(4, 4, 0);

    while (!kb_IsDown(kb_KeyClear)) {
        kb_Scan();

        switch (kb_Data[7]) {
            case kb_Up:
                if (y > 4) {
                    y -= 4;
                }
                direction = 3;
                break;
            case kb_Down:
                if (y < 184) {
                    y += 4;
                }
                direction = 2;
                break;
            case kb_Left:
                if (x > 4) {
                    x -= 4;
                }
                direction = 1;
                break;
            case kb_Right:
                if (x < 270) {
                    x += 4;
                }
                direction = 0;
                break;
            default:
                break;
        }

        car(x, y, direction);
    }

    gfx_End();
}
