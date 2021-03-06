#include "ui.h"
#include "gfx/gfx.h"

#include <graphx.h>
#include <keypadc.h>

void ui_MainMenu(uint8_t day) {
    gfx_FillScreen(17);
    gfx_SetColor(2);
    gfx_Rectangle_NoClip(21, 140, 49, 49);
    gfx_Rectangle_NoClip(78, 140, 49, 49);
    gfx_Rectangle_NoClip(135, 140, 49, 49);
    gfx_Rectangle_NoClip(192, 140, 49, 49);
    gfx_Rectangle_NoClip(249, 140, 49, 49);
    gfx_Rectangle_NoClip(108, 76, 92, 32);
    gfx_Rectangle_NoClip(66, 76, 32, 32);
    gfx_SetColor(0);
    gfx_Rectangle_NoClip(22, 141, 47, 47);
    gfx_Rectangle_NoClip(79, 141, 47, 47);
    gfx_Rectangle_NoClip(136, 141, 47, 47);
    gfx_Rectangle_NoClip(193, 141, 47, 47);
    gfx_Rectangle_NoClip(250, 141, 47, 47);
    gfx_Rectangle_NoClip(109, 77, 90, 30);
    gfx_Rectangle_NoClip(67, 77, 30, 30);
    gfx_SetColor(3);
    gfx_FillRectangle_NoClip(23, 142, 45, 45);
    gfx_FillRectangle_NoClip(80, 142, 45, 45);
    gfx_FillRectangle_NoClip(137, 142, 45, 45);
    gfx_FillRectangle_NoClip(194, 142, 45, 45);
    gfx_FillRectangle_NoClip(251, 142, 45, 45);
    gfx_FillRectangle_NoClip(110, 78, 88, 28);
    gfx_FillRectangle_NoClip(68, 78, 28, 28);

    gfx_SetTextScale(3, 3);
    gfx_PrintStringXY("Into the Shade", 7, 20);
    gfx_PrintStringXY("Play", 112, 80);
    gfx_SetTextScale(2, 2);
    gfx_PrintStringXY("Day ", 109, 208);
    gfx_PrintInt(day + 1, 3);

    gfx_SetTextScale(4, 4);
    gfx_TransparentSprite_NoClip(help, 73, 83);
    gfx_ScaledTransparentSprite_NoClip(greenCarRight, 29, 149, 2, 2);
    if (day >= 20) {
        gfx_ScaledTransparentSprite_NoClip(brownCarRight, 86, 149, 2, 2);
    } else {
        gfx_PrintStringXY("?", 90, 149);
    }
    if (day >= 50) {
        gfx_ScaledTransparentSprite_NoClip(motorcycleRight, 143, 149, 2, 2);
    } else {
        gfx_PrintStringXY("?", 147, 149);
    }
    if (day >= 100) {
        gfx_ScaledTransparentSprite_NoClip(redCarRight, 200, 149, 2, 2);
    } else {
        gfx_PrintStringXY("?", 204, 149);
    }
    if (day >= 200) {
        gfx_ScaledTransparentSprite_NoClip(truckRight, 261, 149, 2, 2);
    } else {
        gfx_PrintStringXY("?", 261, 149);
    }
}

void ui_HelpMenu(void) {
    gfx_FillScreen(17);
    gfx_SetTextScale(3, 3);
    gfx_PrintStringXY("Help", 112, 20);
    gfx_SetColor(0);
    gfx_FillRectangle_NoClip(20, 50, 280, 3);
    gfx_SetTextScale(1, 1);
    gfx_PrintStringXY("Use the arrow keys to move the car", 30, 62);
    gfx_PrintStringXY("around the screen, keeping it from", 30, 72);
    gfx_PrintStringXY("overheating by going in the shade.", 30, 82);
    gfx_PrintStringXY("There are diferent types of weather.", 30, 100);
    gfx_PrintStringXY("In rainy weather, avoid the shade,", 30, 110);
    gfx_PrintStringXY("because of acid rain. Instead, go in", 30, 120);
    gfx_PrintStringXY("the pond. In snowy weather, driving on", 30, 130);
    gfx_PrintStringXY("the frozen pond will cause you to lose", 30, 140);
    gfx_PrintStringXY("control of your vehicle.", 30, 150);
    gfx_PrintStringXY("Try to survive for 256 in-game days", 30, 166);
    gfx_PrintStringXY("in order to win!", 30, 176);
    gfx_PrintStringXY("Cemetech thread: www.ceme.tech/t18578", 30, 192);
    gfx_PrintStringXY("Have fun!", 30, 210);

    while(!kb_IsDown(kb_KeyClear)) {
        kb_Scan();
    }
    while(kb_AnyKey());
}

void ui_ScreenWipe(uint8_t color) {
    gfx_SetColor(color);
    for (uint8_t height = 5; height < 240; height += 5) {
        gfx_FillRectangle_NoClip(0, 0, 320, height);
    }
}

void ui_CarPicked(int x, uint8_t y, uint8_t carType, gfx_sprite_t **carRight) {
    gfx_SetColor(2);
    gfx_Rectangle_NoClip(x, y, 32, 32);
    gfx_SetColor(0);
    gfx_Rectangle_NoClip(x + 1, y + 1, 30, 30);
    gfx_SetColor(3);
    gfx_FillRectangle_NoClip(x + 2, y + 2, 28, 28);
    gfx_TransparentSprite_NoClip(carRight[carType], x + 8, y + 8);
}

void ui_Cursor(int color, int cursorX, uint8_t cursorY) {
    gfx_SetColor(color);
    if (cursorY == 75 && cursorX == 107) {
        gfx_Rectangle_NoClip(cursorX, cursorY, 94, 34);
    } else if (cursorY == 75 && cursorX == 65) {
        gfx_Rectangle_NoClip(cursorX, cursorY, 34, 34);
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
    if (fill > 194) {   // I think this should fix where the heat goes yeet
        fill = 194;
    }
    y = y + (194 - fill);
    gfx_FillRectangle_NoClip(x + 3, y + 3, 14, fill);
}

void ui_BackgroundFrame(uint8_t day) {
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
    gfx_PrintStringXY("Day ", 88, 222);
    gfx_PrintInt(day + 1, 1);
}

void ui_GameOver(void) {
    ui_ScreenWipe(17);

    gfx_SetTextScale(4, 4);
    gfx_SetDrawBuffer();

    gfx_FillScreen(17);

    gfx_SetTextFGColor(0);
    gfx_PrintStringXY("Game Over!", 18, 100);

    gfx_BlitBuffer();

    while (!kb_IsDown(kb_KeyClear)) {
        kb_Scan();
    }
}

void ui_StageComplete(uint8_t day, uint8_t carType, gfx_sprite_t **carRight) {
    ui_ScreenWipe(17);
    int carAnimation = 0;
    gfx_SetDrawBuffer();
    gfx_FillScreen(17);

    gfx_SetTextFGColor(0);
    gfx_SetTextScale(3, 3);
    gfx_PrintStringXY("Day ", 108, 75);
    gfx_PrintInt(day + 1, 1);
    gfx_PrintStringXY("Complete!", 58, 100);
    gfx_SetTextScale(1, 1);
    gfx_PrintStringXY("Press Enter", 119, 145);
    gfx_PrintStringXY("to Save and Continue", 92, 160);

    gfx_BlitBuffer();
    while (!kb_IsDown(kb_KeyEnter) && carAnimation < 288 && !kb_IsDown(kb_KeyClear)) {
        kb_Scan();
        gfx_SetColor(17);
        gfx_FillRectangle_NoClip(carAnimation - 2, 205, 32, 32);
        gfx_ScaledTransparentSprite_NoClip(carRight[carType], carAnimation, 205, 2, 2);
        gfx_BlitBuffer();
        carAnimation += 2;
    }
    ui_ScreenWipe(17);
}

bool ui_Reset(void) {
    while (kb_AnyKey());

    bool reset = false;
    uint8_t cursorY = 107;

    gfx_SetDrawBuffer();
    gfx_FillScreen(17);

    gfx_SetTextScale(2, 2);
    gfx_PrintStringXY("You have completed", 26, 55);
    gfx_PrintStringXY("all 256 days. Reset?", 21, 75);

    gfx_SetColor(2);
    gfx_Rectangle_NoClip(117, 108, 87, 35);
    gfx_Rectangle_NoClip(117, 154, 87, 35);
    gfx_SetColor(0);
    gfx_Rectangle_NoClip(118, 109, 85, 33);
    gfx_Rectangle_NoClip(118, 155, 85, 33);
    gfx_SetColor(3);
    gfx_FillRectangle_NoClip(119, 110, 83, 31);
    gfx_FillRectangle_NoClip(119, 156, 83, 31);

    gfx_SetTextScale(3, 3);
    gfx_PrintStringXY("Yes", 124, 115);
    gfx_PrintStringXY("No", 136, 161);

    gfx_BlitBuffer();

    while (!kb_IsDown(kb_KeyClear) && !kb_IsDown(kb_KeyEnter)) {
        kb_Scan();
        gfx_SetColor(17);
        if (kb_IsDown(kb_KeyDown)) {
            cursorY = 153;
            gfx_Rectangle_NoClip(116, 107, 89, 37);
        } else if (kb_IsDown(kb_KeyUp)) {
            cursorY = 107;
            gfx_Rectangle_NoClip(116, 153, 89, 37);
        }
        gfx_SetColor(0);
        gfx_Rectangle_NoClip(116, cursorY, 89, 37);
        gfx_BlitBuffer();
    }

    if (kb_IsDown(kb_KeyEnter) && cursorY == 107) {
        reset = true;
    }

    return reset;
}

void ui_DYWTSTFC(void) {
    ui_ScreenWipe(17);
    while (kb_AnyKey());

    uint8_t cursorY = 107;

    gfx_FillScreen(17);

    gfx_SetTextScale(2, 2);
    gfx_PrintStringXY("Do you want to see", 26, 55);
    gfx_PrintStringXY("the Flintstone's car?", 21, 75);

    gfx_SetColor(2);
    gfx_Rectangle_NoClip(117, 108, 87, 35);
    gfx_Rectangle_NoClip(117, 154, 87, 35);
    gfx_SetColor(0);
    gfx_Rectangle_NoClip(118, 109, 85, 33);
    gfx_Rectangle_NoClip(118, 155, 85, 33);
    gfx_SetColor(3);
    gfx_FillRectangle_NoClip(119, 110, 83, 31);
    gfx_FillRectangle_NoClip(119, 156, 83, 31);

    gfx_SetTextScale(3, 3);
    gfx_PrintStringXY("Yes", 124, 115);
    gfx_PrintStringXY("No", 136, 161);

    gfx_BlitBuffer();

    while (!kb_IsDown(kb_KeyClear) && !kb_IsDown(kb_KeyEnter)) {
        kb_Scan();
        gfx_SetColor(17);
        if (kb_IsDown(kb_KeyDown)) {
            cursorY = 153;
            gfx_Rectangle_NoClip(116, 107, 89, 37);
        } else if (kb_IsDown(kb_KeyUp)) {
            cursorY = 107;
            gfx_Rectangle_NoClip(116, 153, 89, 37);
        }
        gfx_SetColor(0);
        gfx_Rectangle_NoClip(116, cursorY, 89, 37);
        gfx_BlitBuffer();
    }
    gfx_SetTextScale(2, 2);
    gfx_SetColor(17);

    if (kb_IsDown(kb_KeyEnter) && cursorY == 107) {
        while(kb_AnyKey());
        while (!kb_IsDown(kb_KeyEnter) && !kb_IsDown(kb_KeyClear)) {
            gfx_FillScreen(17);
            gfx_SetTextScale(3, 3);
            gfx_PrintStringXY("Credits:", 72, 20);
            gfx_SetTextScale(2, 2);
            gfx_PrintStringXY("Coding - TIny_Hacker", 12, 56);
            gfx_PrintStringXY("Car Sprites - Edu", 40, 80);
            gfx_PrintStringXY("Support - RoccoLox", 27, 115);
            gfx_SetTextScale(1, 1);
            gfx_PrintStringXY("(edusilvart.itch.io/sprite-stack-cars)", 17, 100);
            gfx_ScaledSprite_NoClip(qr, 127, 140, 2, 2);
            gfx_SetColor(3);
            gfx_Rectangle_NoClip(126, 139, 68, 68);
            gfx_SetColor(0);
            gfx_Rectangle_NoClip(125, 138, 70, 70);
            gfx_SetColor(2);
            gfx_Rectangle_NoClip(124, 137, 72, 72);
            gfx_SetColor(17);
            for (int carX = 0; carX < 288; carX += 2) {
                gfx_FillRectangle_NoClip(carX - 2, 211, 32, 26);
                gfx_ScaledTransparentSprite_NoClip(FC, carX, 205, 2, 2);
                gfx_BlitBuffer();
                kb_Scan();
                if (kb_IsDown(kb_KeyClear) || kb_IsDown(kb_KeyEnter)) {
                    break;
                }
            }
        }
    }
    gfx_BlitBuffer();
}