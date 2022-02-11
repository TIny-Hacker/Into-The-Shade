#ifndef UI_H
#define UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void ui_VerticalIndicator(int, uint8_t, uint8_t, int);

void ui_BackgroundFrame(void);

void ui_GameOver(void);

void ui_StageComplete(void);

#ifdef __cplusplus
}
#endif

#endif
