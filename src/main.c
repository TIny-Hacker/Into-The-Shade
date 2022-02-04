#include "gfx/gfx.h"

#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <stdbool.h>

#define TIMER_FREQ 32768
#define ONE_SECOND (TIMER_FREQ / 1)
#define HALF_SECOND (TIMER_FREQ / 2)
#define THIRD_SECOND (TIMER_FREQ / 3)
#define QRTR_SECOND (TIMER_FREQ / 4)

void draw(shadeX, shadeY, carX, carY, direction) {
    gfx_SetDrawBuffer();

    gfx_FillScreen(2);

    gfx_FillRectangle_NoClip(shadeX, shadeY, 80, 60);
    
    switch (direction) {
        case 0:
            gfx_ScaledTransparentSprite_NoClip(greenCarRight, carX, carY, 3, 3);
            break;
        case 1:
            gfx_ScaledTransparentSprite_NoClip(greenCarLeft, carX, carY, 3, 3);
            break;
        case 2:
            gfx_ScaledSprite_NoClip(greenCarDown, carX, carY, 3, 3);
            break;
        case 3:
            gfx_ScaledSprite_NoClip(greenCarUp, carX, carY, 3, 3);
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
    gfx_SetColor(74);

    uint8_t carY = 4;
    int carX = 4;
    uint8_t shadeY = 50;
    int shadeX = 100;
    uint8_t shadePath = 0;
    uint8_t direction = 0;

    rtc_Enable(RTC_SEC_INT);
    srand(rtc_Time());

    timer_Disable(1);
    timer_Set(1, THIRD_SECOND);
    timer_SetReload(1, THIRD_SECOND);

    draw(100, 50, 4, 4, 0);

    timer_Enable(1, TIMER_32K, TIMER_0INT, TIMER_DOWN);

    while (!kb_IsDown(kb_KeyClear)) {
        kb_Scan();

        switch (kb_Data[7]) {
            case kb_Up:
                if (carY > 4) {
                    carY -= 4;
                }
                direction = 3;
                break;
            case kb_Down:
                if (carY < 184) {
                    carY += 4;
                }
                direction = 2;
                break;
            case kb_Left:
                if (carX > 4) {
                    carX -= 4;
                }
                direction = 1;
                break;
            case kb_Right:
                if (carX < 270) {
                    carX += 4;
                }
                direction = 0;
                break;
            default:
                break;
        }

        if (timer_ChkInterrupt(1, TIMER_RELOADED)) {
            shadePath = randInt(0, 4);
            timer_AckInterrupt(1, TIMER_RELOADED);
        }

        switch (shadePath) {
            case 0:
                if (shadeY > 4) {
                    shadeY -= 2;
                }
                break;
            case 1:
                if (shadeY < 184) {
                    shadeY += 4;
                }
                break;
            case 2:
                if (shadeX > 4) {
                    shadeX -= 4;
                }
                break;
            case 3:
                if (shadeX < 270) {
                    shadeX += 4;
                }
            default:
                break;
        }

        draw(shadeX, shadeY, carX, carY, direction);
    }
    timer_Disable(1);

    gfx_End();
}
