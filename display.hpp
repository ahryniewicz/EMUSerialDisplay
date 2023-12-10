#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

typedef struct {
  String label;
  String *p_value;
  uint16_t warning_color;
  uint16_t error_color;
  boolean warning;
  boolean error;
} display_info_t;

typedef void(*update_t)(display_info_t *p_display_info);

typedef struct {
  uint8_t x;
  uint8_t y;
  uint8_t w;
  uint8_t h;
  display_info_t *p_info;
} display_t;

extern display_t displayMAP;
extern display_t displayAFR;
extern display_t display[3];

void display_init(void);
void update_display(int enc_val, boolean pb_pressed);
#endif