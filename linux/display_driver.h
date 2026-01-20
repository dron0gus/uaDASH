#pragma once

#include "config.h"
#include "lvgl.h"
#include "lv_conf.h"

class LCD_Panel {
  public: LCD_Panel(void);
};

extern LCD_Panel display;
extern int brightnessVal;

#ifdef __cplusplus
extern "C" {
#endif

void setBrightness(int val);

#ifdef __cplusplus
} /*extern "C"*/
#endif

