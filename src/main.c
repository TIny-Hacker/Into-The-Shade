#include "gfx/gfx.h"
#include "ui.h"

#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <stdbool.h>

#define TIMER_FREQ 32768
#define ONE_SECOND (TIMER_FREQ / 1)
#define HALF_SECOND (TIMER_FREQ / 2)
#define THIRD_SECOND (TIMER_FREQ / 3)
#define QRTR_SECOND (TIMER_FREQ / 4)

void draw(int shadeX, uint8_t shadeY, int carX, uint8_t carY, uint8_t direction, uint8_t carType) {
    gfx_sprite_t *carRight[4] = {greenCarRight, brownCarRight, redCarRight, motorcycleRight}; //Different car colors for different directions
    gfx_sprite_t *carLeft[4] = {greenCarLeft, brownCarLeft, redCarLeft, motorcycleLeft};
    gfx_sprite_t *carDown[4] = {greenCarDown, brownCarDown, redCarDown, motorcycleDown};
    gfx_sprite_t *carUp[4] = {greenCarUp, brownCarUp, redCarUp, motorcycleUp};
    
    gfx_SetDrawBuffer();

    gfx_FillScreen(17);

    gfx_SetColor(74);
    gfx_FillRectangle_NoClip(shadeX, shadeY, 80, 60);
    
    switch (direction) {
        case 0:
            if (carType != 4) { // If it's not the truck
                gfx_ScaledTransparentSprite_NoClip(carRight[carType], carX, carY, 3, 3);
            } else {
                gfx_ScaledTransparentSprite_NoClip(truckRight, carX, carY, 3, 3);
            }
            break;
        case 1:
            if (carType != 4) {
                gfx_ScaledTransparentSprite_NoClip(carLeft[carType], carX, carY, 3, 3);
            } else {
                gfx_ScaledTransparentSprite_NoClip(truckLeft, carX, carY, 3, 3);
            }
            break;
        case 2:
            if (carType != 4) {
                gfx_ScaledTransparentSprite_NoClip(carDown[carType], carX, carY, 3, 3);
            } else {
                gfx_ScaledTransparentSprite_NoClip(truckDown, carX, carY, 3, 3);
            }
            break;
        case 3:
            if (carType != 4) {
                gfx_ScaledTransparentSprite_NoClip(carUp[carType], carX, carY, 3, 3);
            } else {
                gfx_ScaledTransparentSprite_NoClip(truckUp, carX, carY, 3, 3);
            }
            break;
        default:
            break;
    }

    ui_verticalIndicator(50, 25, 47, 13);   // Placeholder for the various UI indicators

    gfx_BlitBuffer();
    gfx_SetDrawScreen();
}

int main(void) {
    gfx_Begin();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetTransparentColor(1);

    uint8_t carY = 4;
    int carX = 4;
    uint8_t shadeY = 50;
    int shadeX = 100;
    uint8_t shadePath = 0;
    uint8_t direction = 0;
    uint8_t carType = 0;

    // Weird car picking menu

    gfx_PrintStringXY("Weird car picking menu", 5, 5);
    gfx_PrintStringXY("1 for green car, 2 for brown car, 3 for red car", 5, 15);
    gfx_PrintStringXY("4 for truck, 5 for motorcycle", 5, 25);
    gfx_PrintStringXY("Then press enter.", 5, 35);

    while (!kb_IsDown(kb_KeyEnter)) {
        kb_Scan();
        if (kb_IsDown(kb_Key1)) {
            carType = 0;    // Green car
        } else if (kb_IsDown(kb_Key2)) {
            carType = 1;    // Brown car
        } else if (kb_IsDown(kb_Key3)) {
            carType = 2;    // Red car
        } else if (kb_IsDown(kb_Key4)) {
            carType = 4;    // Truck
        } else if (kb_IsDown(kb_Key5)) {
            carType = 3;    // Motorcycle (these are backwards because of weird things with arrays)
        }
    }

    rtc_Enable(RTC_SEC_INT);
    srand(rtc_Time());

    timer_Disable(1);
    timer_Set(1, THIRD_SECOND);
    timer_SetReload(1, THIRD_SECOND);

    draw(100, 50, 4, 4, 0, carType);

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

        draw(shadeX, shadeY, carX, carY, direction, carType);
    }
    timer_Disable(1);

    gfx_End();
}
