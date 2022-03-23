#ifndef UI_H
#define UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <graphx.h>

void ui_MainMenu(void);

void ui_CarPicked(uint16_t, uint8_t, uint8_t, gfx_sprite_t **);

void ui_Cursor(uint16_t, uint16_t, uint8_t);

void ui_VerticalIndicator(int, uint8_t, uint8_t, int);

void ui_BackgroundFrame(uint8_t);

void ui_GameOver(void);

void ui_StageComplete(uint8_t, uint8_t, gfx_sprite_t **);

#ifdef __cplusplus
}
#endif

#endif
