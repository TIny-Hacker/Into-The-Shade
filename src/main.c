#include "gfx/gfx.h"
#include "ui.h"

#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <stdbool.h>
#include <fileioc.h>

#define TIMER_FREQ 32768
#define ONE_SECOND (TIMER_FREQ / 1)
#define HALF_SECOND (TIMER_FREQ / 2)
#define THIRD_SECOND (TIMER_FREQ / 3)
#define QRTR_SECOND (TIMER_FREQ / 4)

void draw(int shadeX, uint8_t shadeY, int carX, uint8_t carY, uint8_t direction, uint8_t carType, uint8_t heat, int time, gfx_sprite_t **carRight, gfx_sprite_t **carLeft, gfx_sprite_t **carUp, gfx_sprite_t **carDown) {
    gfx_BlitScreen();    
    gfx_SetDrawBuffer();

    gfx_SetColor(3);
    gfx_FillRectangle_NoClip(23, 21, 204, 194); // Background

    gfx_ScaledTransparentSprite_NoClip(roadPuddle, 154, 42, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(roadCrack, 83, 139, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(roadCrack, 56, 84, 2, 2);

    gfx_SetColor(74);
    gfx_FillRectangle_NoClip(shadeX, shadeY, 80, 60);   // Shade
    
    switch (direction) {
        case 0:
                gfx_ScaledTransparentSprite_NoClip(carRight[carType], carX, carY, 3, 3);
            break;
        case 1:
                gfx_ScaledTransparentSprite_NoClip(carLeft[carType], carX, carY, 3, 3);
            break;
        case 2:
                gfx_ScaledTransparentSprite_NoClip(carDown[carType], carX, carY, 3, 3);
            break;
        case 3:
                gfx_ScaledTransparentSprite_NoClip(carUp[carType], carX, carY, 3, 3);
            break;
        default:
            break;
    }

    ui_VerticalIndicator(251, 18, 47, time);   // Time and heat indicators
    ui_VerticalIndicator(279, 18, 160, heat);

    gfx_BlitBuffer();
    gfx_SetDrawScreen();
}

int main(void) {
    uint8_t shadeVar[2] = {0, 0};

    ti_var_t slot = ti_Open("SHADE", "r");    // Appvar with preferences/progress

    if (slot) {
        ti_Read(&shadeVar, 2, 1, slot);

    }

    gfx_Begin();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetTransparentColor(1);

    uint8_t carType = shadeVar[0];
    uint8_t day = shadeVar[1];

    gfx_sprite_t *carRight[5] = {greenCarRight, brownCarRight, redCarRight, truckRight, motorcycleRight}; //Different car colors for different directions
    gfx_sprite_t *carLeft[5] = {greenCarLeft, brownCarLeft, redCarLeft, truckLeft, motorcycleLeft};
    gfx_sprite_t *carDown[5] = {greenCarDown, brownCarDown, redCarDown, truckDown, motorcycleDown};
    gfx_sprite_t *carUp[5] = {greenCarUp, brownCarUp, redCarUp, truckUp, motorcycleUp};

    // Main menu

    gfx_SetDrawBuffer();
    ui_MainMenu();
    ui_CarPicked(210, 76, carType, &carRight[0]);   // Whenever I pass an array of sprites, the compiler has a hiccup unless I put a [0] after it. Not sure why but it works!
    gfx_BlitBuffer();

    uint16_t cursorX = 107;
    uint8_t cursorY = 75;

    gfx_SetDrawScreen();
    ui_Cursor(0, cursorX, cursorY);
    
    while (kb_AnyKey());

    bool keyPressed = false;
    timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);

    while (!(kb_IsDown(kb_KeyEnter) && cursorY == 75)) {
        kb_Scan();
        if (!kb_AnyKey()) {
            keyPressed = false;
            timer_Set(1, 0);
        }
        if (kb_IsDown(kb_KeyEnter) && cursorY != 75) {
            if (cursorX == 20) {
                carType = 0;
            } else if (cursorX == 77) {
                carType = 1;
            } else if (cursorX == 134) {
                carType = 4;
            } else if (cursorX == 191) {
                carType = 2;
            } else if (cursorX == 248) {
                carType = 3;
            }
            ui_CarPicked(210, 76, carType, &carRight[0]);
        }
        if (kb_Data[7] && (!keyPressed || timer_Get(1) > 3000)) {
            ui_Cursor(17, cursorX, cursorY);
            if (kb_IsDown(kb_KeyDown)) {
                cursorY = 139;
                cursorX = 20;
            } else if (kb_IsDown(kb_KeyUp)) {
                cursorY = 75;
                cursorX = 107;
            } else if (kb_IsDown(kb_KeyRight) && cursorX < 193 && cursorY != 75) {
                cursorX += 57;
            } else if (kb_IsDown(kb_KeyLeft) && cursorX > 20 && cursorY != 75) {
                cursorX -= 57;
            }
            ui_Cursor(0, cursorX, cursorY);
            if (!keyPressed) {
                while (timer_Get(1) < 9000 && kb_Data[7]) {
                    kb_Scan();
                }
            }
            keyPressed = true;
            timer_Set(1,0);
        }
    }


    // Actual game stuff
    rtc_Enable(RTC_SEC_INT);
    srand(rtc_Time());
    timer_Disable(1);
    timer_Set(1, THIRD_SECOND);
    timer_SetReload(1, THIRD_SECOND);

    for (day = shadeVar[1]; day <= 255; day++) {
        uint8_t carY = 23;
        int carX = 25;
        uint8_t shadeY = 50;
        int shadeX = 100;
        uint8_t shadePath = 0;
        uint8_t direction = 0;
        uint8_t heat = 0;
        int time = 0;
        int finish = 150;

        gfx_SetDrawBuffer();
        ui_BackgroundFrame(day);
        gfx_BlitBuffer();

        draw(100, 50, carX, carY, 0, carType, heat, 0, &carRight[0], &carLeft[0], &carUp[0], &carDown[0]);

        while (kb_AnyKey());
        timer_Enable(1, TIMER_32K, TIMER_0INT, TIMER_DOWN);

        while (!kb_IsDown(kb_KeyClear)) {
            kb_Scan();

            switch (kb_Data[7]) {
                case kb_Up:
                    if (carY > 23) {
                        carY -= 4;
                    }
                    direction = 3;
                    break;
                case kb_Down:
                    if (carY < 158) {
                        carY += 4;
                    }
                    direction = 2;
                    break;
                case kb_Left:
                    if (carX > 25) {
                        carX -= 4;
                    }
                    direction = 1;
                    break;
                case kb_Right:
                    if (carX < 182) {
                        carX += 4;
                    }
                    direction = 0;
                    break;
                default:
                    break;
            }

            if (timer_ChkInterrupt(1, TIMER_RELOADED)) {
                shadePath = randInt(0, 4);
                if (carX >= shadeX - 10 && carY >= shadeY - 10 && carX <= shadeX + 70 && carY <= shadeY + 50) {   // If the car is in the shade
                    heat -= (heat > 0);
                } else {
                    heat += (heat < 99) * 2;
                }
                time++;
                timer_AckInterrupt(1, TIMER_RELOADED);
            }

            switch (shadePath) {
                case 0:
                    if (shadeY > 24) {
                        shadeY -= 4;
                    }
                    break;
                case 1:
                    if (shadeY < 152) {
                        shadeY += 4;
                    }
                    break;
                case 2:
                    if (shadeX > 25) {
                        shadeX -= 4;
                    }
                    break;
                case 3:
                    if (shadeX < 144) {
                        shadeX += 4;
                    }
                default:
                    break;
            }

            draw(shadeX, shadeY, carX, carY, direction, carType, heat, (time * 100 / finish), &carRight[0], &carLeft[0], &carUp[0], &carDown[0]);

            if (heat >= 100) {
                boot_WaitShort();
                ui_GameOver();
                break;
            }

            if (time >= finish) {
                boot_WaitShort();
                ui_StageComplete(day, carType, &carRight[0]);
                while (kb_AnyKey());
                break;
            }
        }
        if (kb_IsDown(kb_KeyClear)) {
            break;
        }
    }
    timer_Disable(1);

    gfx_End();

    // Finish up my appvar stuff

    shadeVar[0] = carType;
    shadeVar[1] = day;

    slot = ti_Open("SHADE", "w+");

    ti_Write(&shadeVar, 2, 1, slot);

    ti_SetArchiveStatus(true, slot);

    return 0;
}
