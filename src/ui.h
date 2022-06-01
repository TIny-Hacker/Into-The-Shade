#ifndef UI_H
#define UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <graphx.h>
#include <stdbool.h>

void ui_MainMenu(uint8_t);

void ui_HelpMenu(void);

void ui_ScreenWipe(uint8_t);

void ui_CarPicked(int, uint8_t, uint8_t, gfx_sprite_t **);

void ui_Cursor(int, int, uint8_t);

void ui_VerticalIndicator(int, uint8_t, uint8_t, int);

void ui_BackgroundFrame(uint8_t);

void ui_GameOver(void);

void ui_StageComplete(uint8_t, uint8_t, gfx_sprite_t **);

bool ui_Reset(void);

void ui_DYWTSTFC(void);

#ifdef __cplusplus
}
#endif

#endif
